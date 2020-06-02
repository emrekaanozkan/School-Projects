%% SINGLE PARITY CHECK - EVEN
    clear;
    %MESSAGE PREPARING 
    disp("Program Starting")
    message = 'E'; %Input Message
    disp("Message :")
    disp(message)
    binary_message = dec2bin(message); %Message to binary
    %Resize
    msg = reshape(binary_message,[],1);
    msg = str2num(msg);
    msg = reshape(msg,[],7);
    
    len_row = length(msg(:,1));
    len_column = length(msg);
    
    %ENCODING 
    for row=1:(len_row)
        row_sum(row) = mod(sum(msg(row,1:end)),2); %adding parity bit
    end
    disp("MESSAGE With Parity Bit")
    matrix = [msg row_sum']; %concat parity bit
    disp(matrix)
    
    %CHANNEL ERROR
    matrix(3) = ~matrix(3); %adding error
    disp("Error With Matrix");
    disp(matrix)
    
    %DECODING - ERROR DETECTION
    for row=1:(len_row)
       if row_sum(row) ~= mod(sum(matrix(row,1:end-1)),2) %parity check
           disp("Error Detected 're-transmission!' ")
           %disp(row)
       else
           disp("No Error! ")
           %disp(row)
       end
    end
    matrix = matrix(:,1:end-1); %Drop Parity Bit
    %Message preparing for ASCII
    received_matrix = char(reshape(char('0' + matrix),[],7));
    received_message = char(bin2dec(received_matrix));
    received_message = reshape(received_message,[],length(message));
    disp("Received Message ")
    disp(received_message)
    
    



            
        
        