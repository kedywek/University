import java.util.Random;
import java.util.Scanner;

class loops{
    public static void main(String args[]){  
        Random rand = new Random();
        Scanner reader = new Scanner(System.in);
        int gameState = 1;
        int guess, randomNumber, counter;
        while(gameState == 1){
            System.out.println("Guess a number");
            guess = reader.nextInt();
            randomNumber = rand.nextInt(101);
            counter = 0;
            while (guess != randomNumber) {
                counter ++;
                if (guess > randomNumber){
                    System.out.println("Number is smaller");
                }
                else{
                    System.out.println("Number is bigger");
                }
                System.out.println("Guess again");
                guess = reader.nextInt();
            }
            System.out.println("You guessed in "+counter+" attempts");
            System.out.println("Would you like to play again? input Y or N");
            String answear = reader.nextLine();
            do {
                if(answear == "Y"){
    
                }
                else if(answear == "N"){
                    gameState = 0;
                }
                else{
                    System.out.println("Incorrect Input(not Y or N)");
                    answear = reader.nextLine();
                }
            } while (answear == "Y" || answear == "N");
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