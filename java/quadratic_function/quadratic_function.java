import java.lang.Math; 

class quadratic{
    public static void main(String[] args){
        int a, b, c;
        if(args.length == 3){
            a = Integer.parseInt(args[0]);
            b = Integer.parseInt(args[1]);
            c = Integer.parseInt(args[2]); 
            double delta = b*b - 4 * a * c;
            System.out.println(delta);
            if (delta < 0){
                System.out.println("There is no real root");
            }else{
                double x1 = (-b + Math.sqrt(delta)) / (2 * a), x2 = (-b - Math.sqrt(delta)) / (2 * a);
                System.out.println("x1 = " + x1 + " x2 = " + x2);
            }
        }
        else{
            System.out.println("You should provide 3 arguments");
        }

    }
}