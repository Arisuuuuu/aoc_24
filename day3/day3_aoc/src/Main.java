import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;

public class Main {
    //who cares about error handling in such cases
    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("input3.txt"));
        List<String> text = new LinkedList<>();
        int sum = 0;
        while(sc.hasNextLine()) {
            text.add(sc.nextLine());
        }
        sc.close();
        System.out.println("part1 answer: " + part1(text));
        System.out.println("part2 answer: " + part2(text));
    }

    public static int part1(List<String> text){
        int sum = 0;
        for(String s : text){
            Matcher matcher_mul  = Pattern.compile("[m]{1}[u]{1}[l]{1}[(]{1}[0-9]+[,]{1}[0-9]+[)]{1}").matcher(s);
            while(matcher_mul.find()){
                Matcher matcher_reg = Pattern.compile("\\d+").matcher(s.substring(matcher_mul.start(), matcher_mul.end()));
                matcher_reg.find();
                int num1 = Integer.valueOf(s.substring(matcher_mul.start(), matcher_mul.end()).substring(matcher_reg.start(), matcher_reg.end()));
                matcher_reg.find();
                int num2  = Integer.valueOf(s.substring(matcher_mul.start(), matcher_mul.end()).substring(matcher_reg.start(), matcher_reg.end()));
                sum+=num1*num2;
            }
        }
        return sum;
    }

    public static int part2(List<String> text){
        int sum = 0;
        for(String s : text){
            Matcher matcher_mul  = Pattern.compile("[m]{1}[u]{1}[l]{1}[(]{1}[0-9]+[,]{1}[0-9]+[)]{1}").matcher(s);
            while(matcher_mul.find()){
                if(s.substring(0, matcher_mul.start()).lastIndexOf("do()") >= s.substring(0, matcher_mul.start()).lastIndexOf("don't()")) {
                    Matcher matcher_reg = Pattern.compile("\\d+").matcher(s.substring(matcher_mul.start(), matcher_mul.end()));
                    matcher_reg.find();
                    int num1 = Integer.valueOf(s.substring(matcher_mul.start(), matcher_mul.end()).substring(matcher_reg.start(), matcher_reg.end()));
                    matcher_reg.find();
                    int num2 = Integer.valueOf(s.substring(matcher_mul.start(), matcher_mul.end()).substring(matcher_reg.start(), matcher_reg.end()));
                    sum += num1 * num2;
                   // System.out.println("do: " + s.substring(0, matcher_mul.start()).lastIndexOf("do()") + "; " + s.substring(0, matcher_mul.start()).lastIndexOf("don't()") + ", mul: " + num1 + "*" + num2);

                }
            }

        }
        return sum;
    }
}