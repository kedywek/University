import java.util.Scanner;
import java.util.Vector;
import java.io.IOException;


class InputController {
    public static void main(String[] args) {
        boolean isRunning = true;
        Scanner scanner = new Scanner(System.in);

        while (isRunning) {
            VectorAdder vectorAdder = new VectorAdder();
            vectorAdder = processInput(vectorAdder, scanner);
            try {
                System.out.println(vectorAdder.sumVectors());
                isRunning = false;
            }
            catch (DifferentVectorsLengthsException e) {
                System.out.println(e.getMessage()); 
                System.out.println("Re-enter the vectors");
            }
        }
        scanner.close();
    }

    public static VectorAdder processInput(VectorAdder vectorAdder, Scanner scanner) {
        try {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (line.isEmpty()) {
                    break;
                }
                Vector<Double> vector = extractVectorfromString(line);
                vectorAdder.addVector(vector);
            }
        }
        catch (Exception e) {
            System.out.println("Error reading input");
        }
        return vectorAdder;
    }

    public static  Vector<Double> extractVectorfromString(String input)  {
        Vector<Double> vector = new Vector<>();
        String[] values = input.split(",");
        for (String value : values) {
            try{
                vector.add(Double.parseDouble(value));
            }
            catch (NumberFormatException e){
                
            }
        }
        return vector;
    }
}