import java.util.Scanner;

public class InputController {
    public static void main(String[] args) {
        ShoppingList shoppingList = new ShoppingList();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println();
            System.out.println("1. Add a category");
            System.out.println("2. Add a product");
            System.out.println("3. Remove a category");
            System.out.println("4. Remove a product");
            System.out.println("5. Print the list");
            System.out.println("6. Save and exit");
            System.out.println("7. Exit without saving");
            System.out.println("Enter your choice: ");
            String choice = scanner.nextLine();
            switch (choice) {
                case "1":
                    addCategory(scanner, shoppingList);
                    break;
                case "2":
                    addProduct(scanner, shoppingList);
                    break;
                case "3":
                    removeCategory(scanner, shoppingList);
                    break;
                case "4":
                    removeProduct(scanner, shoppingList);
                    break;
                case "5":
                    shoppingList.printList();
                    break;
                case "6":
                    shoppingList.saveAndExit();
                    System.exit(0);
                    scanner.close();
                    break;
                case "7":
                    System.exit(0);
                    scanner.close();
                    break;
                default:
                    System.out.println("Invalid choice");
                    break;
            }
        }
    }

    public static void addCategory(Scanner scanner, ShoppingList shoppingList) {
        String categoryName = getStringInput(scanner, "Enter the name of the category: ");
        if (shoppingList.checkCategory(categoryName)) {
            System.out.println("Category already exists");
        } else {
            shoppingList.addCategory(categoryName);
        }
    }

    public static void addProduct(Scanner scanner, ShoppingList shoppingList) {
        String categoryName = getStringInput(scanner, "Enter the name of the category: ");
        if (shoppingList.checkCategory(categoryName)) {
            String productName = getStringInput(scanner, "Enter the name of the product: ");
            shoppingList.addProduct(productName, categoryName);
        } else {
            System.out.println("Category does not exist");
        }
    }

    public static void removeCategory(Scanner scanner, ShoppingList shoppingList) {
        String categoryName = getStringInput(scanner, "Enter the name of the category: ");
        shoppingList.removeCategory(categoryName);
    }

    public static void removeProduct(Scanner scanner, ShoppingList shoppingList) {
        String categoryName = getStringInput(scanner, "Enter the name of the category: ");
        if (shoppingList.checkCategory(categoryName)) {
            String productName = getStringInput(scanner, "Enter the name of the product: ");
            shoppingList.removeProduct(productName, categoryName);
        } else {
            System.out.println("Category does not exist");
        }
    }

    public static String getStringInput(Scanner scanner, String message) {
        System.out.println(message);
        return scanner.nextLine();
    }

    public static int checkValidInteger(String input, String error) {
        try {
            int a = Integer.parseInt(input);
            return a;
        } catch (NumberFormatException e) {
            System.out.println(error);
            return -1;
        }
    }
}