import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class FileHandling {
    public static String readFile(String fileName) {
        String data = "";
        try {
            File file = new File(fileName);
            if (file.exists()) {
                Scanner reader = new Scanner(file);
                while (reader.hasNextLine()) {
                    data += reader.nextLine() + "\n";
                }
                reader.close();
            } else {
                file.createNewFile();
            }
        } catch (IOException e) {
            System.out.println("An error has occurred.");
            e.printStackTrace();
        }
        return data;
    }

    public static void writeFile(String fileName, String data) {
        try {
            File file = new File(fileName);
            if (file.exists()) {
                file.delete();
            }
            file.createNewFile();
            java.nio.file.Files.write(file.toPath(), data.getBytes(), java.nio.file.StandardOpenOption.APPEND);
        } catch (IOException e) {
            System.out.println("An error has occurred.");
            e.printStackTrace();
        }
    }
}