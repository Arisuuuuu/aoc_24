module day2;

    int file; 
    int num, prev_num, char,code;
    int operation; //0 uknown -1 decrease 1 increase 
    int part1_cnt = 0; 
    int part2_cnt = 0; 
    int error; 
    int data[]= new[0];


    initial begin

        file = $fopen("input2.txt", "r");
        if(!file) begin 
            $display("error opening file !");
            $finish;
        end

        $display(data.size());


    
        while(!$feof(file)) begin
            code = $fscanf(file, "%d%c", num, char);
            data = new[data.size() + 1](data);
            data[data.size() - 1] = num;

            prev_num = num;

            if(char == "\n") begin 
                part1_cnt += calcPart1(data);
                part2_cnt += calcPart2(data);
                data = new[0];
            end
        end

        part1_cnt += calcPart1(data);
        part2_cnt += calcPart2(data);

        $display("part1 answer: ", part1_cnt);
        $display("part2 answer: ", part2_cnt);

        $fclose(file);
    
    end

    function automatic int calcPart1(int row[]);
        int decrease = 0; 
        int increase = 0; 
        for(int i = 0; i < row.size() - 1; i++) begin 
            if(row[i] > row[i+1] || (row[i] - row[i+1] < -3)) begin 
                decrease++; 
            end
            if(row[i] < row[i+1] || (row[i] - row[i+1]> 3)) begin 
                increase++;
            end
            if(row[i] == row[i+1]) begin 
                return 0;
            end;
        end
        if(increase == 0 || decrease == 0) begin 
            return 1;
        end
        return 0;
    endfunction

    function automatic int calcPart2(int row[]);

    
        int merge1[] = new[row.size() -1];
        int merge2[] = new[row.size() -1];
    
       

        for(int i = 0; i < row.size() - 1; i++) begin 

            //dynimacally slicing arrays and merging them doesnt work
            for(int j = 0; j < row.size(); j++) begin 
                if(j < i) begin 
                    merge1[j] = row[j];
                end
                if(j > i) begin 
                    merge1[j-1] = row[j];
                end
                if(j < i+1) begin 
                    merge2[j] = row[j];
                end
                if(j > i+1) begin 
                    merge2[j-1] = row[j];
                end
            end


            if(row[i] < row[i+1] || (row[i] - row[i+1]> 3))begin 
                if(calcPart1(merge1)) begin 
                    return 1; 
                end
                if(calcPart1(merge2)) begin 
                    return 1; 
                end
            end

         
            if(row[i] > row[i+1] || (row[i] - row[i+1] < -3)) begin 
                if(calcPart1(merge1)) begin 
                    return 1; 
                end

                if(calcPart1(merge2)) begin 
                    return 1; 
                end
            end
        end
        return 0;
    endfunction;



  
endmodule