%% TWO DIMENSIONAL PARITY CHECK CODE 
    clear;
    %MESSAGE and PREPARING
    disp("Program Starting")
    message = 'Kaan'; %Input Message
    disp("Message : ")
    disp(message)
    %Resize
    binary_message = dec2bin(message);
    msg = reshape(binary_message,[],1);
    msg = str2num(msg);
    msg = reshape(msg,[],7);
    
         
    len_row = length(msg(:,1));
    len_column = length(msg);
    error_row = 0;
    error_column = 0;
    error_row_sum = 0;
    error_col_sum = 0;
    
   %ENCODING
    for row=1:(len_row)
        row_sum(row) = mod(sum(msg(row,1:end)),2); %adding parity row
    end
    matrix = [msg row_sum']; %concat parity row
    for col=1:len_column+1
        col_sum(col)= mod(sum(matrix(1:end,col)),2); %adding parity column
    end
    matrix = [matrix;col_sum]; %concat cheksum column
    disp("Code : ")
    disp(matrix) 
  
    %CHANNEL ERROR
    matrix(3,1) = ~matrix(3,1); % add one bit error
    disp("Code with Error Bit : ")
    disp(matrix)
  
    %%%% FIND-CORRECT ERROR AND DECODING%%%
%find error row
    for row=1:(len_row)
        x = mod(sum(matrix(row,1:end-1)),2);
        if x~= matrix(row,end)
            error_row = row
            error_row_sum = x;
        end
    end

    %find error column
    for col=1:(len_column)
        y = mod(sum(matrix(1:end-1,col)),2);
        if y ~= matrix(end,col)
            error_column = col
            error_col_sum = y ; 
        end
    end    
    %When no error or the only error is the sum of all parity(right-bottom corner)
    if error_row == 0 && error_column == 0
            disp("No error or Right Buttom Error")
            matrix(len_row+1,len_column+1) = mod(sum(matrix(len_row+1,1:len_column)),2)
    %When the error is parity row
    elseif error_row == 0 && error_column ~= 0
        m = 0;
        for row=1:(len_row-1)
            m = matrix(row,error_column)+m
        end
        matrix(end,error_column) = m
    
    %When the error is parity column
    elseif error_row ~= 0 && error_column == 0
        n=0;
        for col=1:(len_column-1)
            n = matrix(error_row,col)+n;
        end
        matrix(error_row,end) = n;
        
    else
        matrix(error_row,error_column) = matrix(error_row,error_column) - (error_row_sum -matrix(error_row,end));
    end
    disp("Corrected Code")
    disp(matrix)
    matrix = mod(matrix,2); 
    
    %Message Preparing for ASCII
    matrix = matrix(1:end-1,1:end-1);
    received_matrix = char(reshape(char('0' + matrix),[],7));
    received_message = char(bin2dec(received_matrix));
    received_message = reshape(received_message,[],length(message));
    disp("Corrected Received Message ")
    disp(received_message)
    