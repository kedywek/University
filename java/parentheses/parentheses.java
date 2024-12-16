import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class parentheses{
    public static void main(String args[]){
        if (args.length == 1){  
            if (check(args[0])) {
                System.out.println("Parentheses match");
            }else{
                System.out.println("Parentheses doesn't match");
            }

        }
        else{
        System.out.println("Give just 1 argument");
        }
    }
    public static boolean check(String input){
        Stack<Character> stack = new Stack<>();
        Pattern parentheses = Pattern.compile("[(){}\\[\\]]");
        Matcher matcher = parentheses.matcher(input);
        while (matcher.find()){
            char current = matcher.group().charAt(0);
            if (current == '(' || current == '{' || current == '['){
                stack.push(current);
            }
            else{
                if (stack.isEmpty() || !isMatchingParentheses(stack.pop(), current)){
                    return false;
                }
            }
        }
        if (stack.isEmpty()){
            return true;
        }
        else{
            return false;
        }
    }
    public static boolean isMatchingParentheses(char opening, char closing){
        return(opening == '(' && closing == ')' || opening == '{' && closing == '}'|| opening == '[' && closing == ']');
    }
}