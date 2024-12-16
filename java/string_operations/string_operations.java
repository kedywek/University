class stringOperation{
    public static void main(String[] args){
        if(args.length == 3){
            int a = checkValidInteger(args[1], "Second argument have to be a number"), b = checkValidInteger(args[2],"Third argument have to be a number");
            if(a < 0){
                System.out.println("Second argument have to be positive");
            }else if(b > args[0].length()){
                System.out.println(args[0].substring(a));
                StringBuffer rest = new StringBuffer(args[0]);
                rest.replace(a, args[0].length(), "");
                System.out.println(rest);

            }
            else{
                System.out.println(args[0].substring(a, b));
                StringBuffer rest = new StringBuffer(args[0]);
                rest.replace(a, b, "");
                System.out.println(rest);
            }
        }
    }
    public static int checkValidInteger(String input, String error){
        try{
             int a = Integer.parseInt(input);
             return a;
             
        } catch(NumberFormatException e){
            System.out.println(error);
            return -1;
        }
    }
}