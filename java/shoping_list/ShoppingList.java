import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

class InputController {
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
            try {
                Integer.parseInt(choice);
            } catch (NumberFormatException e) {
                System.out.println("Invalid choice");
                continue;
            }
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
        return scanner.nextLine().trim();
    }
}

class ShoppingList {
    private List<Category> categories = new ArrayList<Category>();

    public ShoppingList() {
        String data = FileHandling.readFile("shopping_list.csv");
        createShoppingListFromString(data);
    }

    public void addCategory(String categoryName) {
        Category newCategory = new Category(categoryName);
        categories.add(newCategory);
    }

    public void removeCategory(String categoryName) {
        if (checkCategory(categoryName)) {
            for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
                if (categories.get(categoryIndex).getName().equals(categoryName)) {
                    categories.remove(categoryIndex);
                }
            }
        } else {
            System.out.println("Category does not exist");
        }
    }

    public void addProduct(String productName, String categoryName) {
        if (checkCategory(categoryName)) {
            for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
                if (categories.get(categoryIndex).getName().equals(categoryName)) {
                    categories.get(categoryIndex).addItem(new Product(productName));
                }
            }
        }
    }

    public void removeProduct(String productName, String categoryName) {
        if (checkCategory(categoryName)) {
            for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
                if (categories.get(categoryIndex).getName().equals(categoryName)) {
                    categories.get(categoryIndex).removeItem(productName);
                }
            }
        }
    }

    public void printList() {
        System.out.println("\nShopping List:");
        for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
            System.out.print("\n" + categories.get(categoryIndex).getName() + ":\n");
            for (int itemIndex = 0; itemIndex < categories.get(categoryIndex).items.size(); itemIndex++) {
                System.out.print("    " + categories.get(categoryIndex).items.get(itemIndex).getName() + "\n");
            }
        }
        System.out.println();
    }

    public void createShoppingListFromString(String data) {
        String[] lines = data.split("\n");
        for (int lineIndex = 0; lineIndex < lines.length; lineIndex++) {
            String[] category = lines[lineIndex].split(":");
            Category newCategory = new Category(category[0].trim());
            if (category.length == 2) {
                String[] items = category[1].split(";");
                for (int itemIndex = 1; itemIndex < items.length; itemIndex++) {
                    newCategory.items.add(new Product(items[itemIndex].trim()));
                }
            }
            categories.add(newCategory);
        }
    }

    public String extractDataToString() {
        String data = "";
        for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
            data += categories.get(categoryIndex).getName() + ":;";
            for (int itemIndex = 0; itemIndex < categories.get(categoryIndex).items.size(); itemIndex++) {
                data += categories.get(categoryIndex).items.get(itemIndex).getName();
                if (itemIndex != categories.get(categoryIndex).items.size() - 1) {
                    data += ";";
                }
            }
            if (categoryIndex != categories.size() - 1) {
                data += "\n";
            }
        }
        return data;
    }

    public void saveAndExit() {
        String data = extractDataToString();
        FileHandling.writeFile("shopping_list.csv", data);
    }

    public boolean checkCategory(String name) {
        for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
            if (categories.get(categoryIndex).getName().equals(name)) {
                return true;
            }
        }
        return false;
    }

    public boolean checkItem(String name) {
        for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
            if (categories.get(categoryIndex).checkItem(name)) {
                return true;
            }
        }
        return false;
    }

    public void swapCategories(Category category1, String name) {
        if (checkCategory(name)) {
            for (int categoryIndex = 0; categoryIndex < categories.size(); categoryIndex++) {
                if (categories.get(categoryIndex).getName().equals(name)) {
                    categories.set(categoryIndex, category1);
                }
            }
        }
    }
}

class Category {
    private String name;
    List<Product> items = new ArrayList<Product>();

    public Category(String newName) {
        name = newName;
    }

    public void addItem(Product item) {
        items.add(item);
    }

    public String getName() {
        return name;
    }

    public void swapItems(Product item1, String name) {
        if (checkItem(name)) {
            for (int itemIndex = 0; itemIndex < items.size(); itemIndex++) {
                if (items.get(itemIndex).getName().equals(name)) {
                    items.set(itemIndex, item1);
                }
            }
        }
    }

    public void removeItem(String item) {
        if (checkItem(item)) {
            for (int itemIndex = 0; itemIndex < items.size(); itemIndex++) {
                if (items.get(itemIndex).getName().equals(item)) {
                    items.remove(itemIndex);
                }
            }
        }
    }

    public boolean checkItem(String name) {
        for (int itemIndex = 0; itemIndex < items.size(); itemIndex++) {
            if (items.get(itemIndex).getName().equals(name)) {
                return true;
            }
        }
        return false;
    }
}

class Product {
    private String name;

    public Product(String newName) {
        name = newName;
    }

    public String getName() {
        return name;
    }
}

class FileHandling {
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
