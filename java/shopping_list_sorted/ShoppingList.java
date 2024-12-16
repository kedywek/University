import java.util.ArrayList;
import java.util.List;

public class ShoppingList {
    private List<Category> categories = new ArrayList<Category>();

    public ShoppingList() {
        String data = FileHandling.readFile("shopping_list.csv");
        getDataFromString(data);
    }

    public void addCategory(String categoryName) {
        Category newCategory = new Category(categoryName);
        categories.add(newCategory);
    }

    public void removeCategory(String categoryName) {
        if (checkCategory(categoryName)) {
            for (int i = 0; i < categories.size(); i++) {
                if (categories.get(i).getName().equals(categoryName)) {
                    categories.remove(i);
                }
            }
        } else {
            System.out.println("Category does not exist");
        }
    }

    public void addProduct(String productName, String categoryName) {
        if (checkCategory(categoryName)) {
            for (int i = 0; i < categories.size(); i++) {
                if (categories.get(i).getName().equals(categoryName)) {
                    categories.get(i).addItem(new Product(productName));
                }
            }
        }
    }

    public void removeProduct(String productName, String categoryName) {
        if (checkCategory(categoryName)) {
            for (int i = 0; i < categories.size(); i++) {
                if (categories.get(i).getName().equals(categoryName)) {
                    categories.get(i).removeItem(productName);
                }
            }
        }
    }

    public void printList() {
        System.out.println("\nShopping List:");
        for (int i = 0; i < categories.size(); i++) {
            System.out.print("\n" + categories.get(i).getName() + ":\n");
            for (int j = 0; j < categories.get(i).items.size(); j++) {
                System.out.print("    " + categories.get(i).items.get(j).getName() + "\n");
            }
        }
        System.out.println();
    }

    public void getDataFromString(String data) {
        String[] lines = data.split("\n");
        for (int i = 0; i < lines.length; i++) {
            String[] category = lines[i].split(":");
            Category newCategory = new Category(category[0].trim());
            if (category.length == 2) {
                String[] items = category[1].split(";");
                for (int j = 1; j < items.length; j++) {
                    newCategory.items.add(new Product(items[j].trim()));
                }
            }
            categories.add(newCategory);
        }
    }

    public String extractDataToString() {
        String data = "";
        for (int i = 0; i < categories.size(); i++) {
            data += categories.get(i).getName() + ":;";
            for (int j = 0; j < categories.get(i).items.size(); j++) {
                data += categories.get(i).items.get(j).getName();
                if (j != categories.get(i).items.size() - 1) {
                    data += ";";
                }
            }
            if (i != categories.size() - 1) {
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
        for (int i = 0; i < categories.size(); i++) {
            if (categories.get(i).getName().equals(name)) {
                return true;
            }
        }
        return false;
    }

    public boolean checkItem(String name) {
        for (int i = 0; i < categories.size(); i++) {
            if (categories.get(i).checkItem(name)) {
                return true;
            }
        }
        return false;
    }

    public void swapCategories(Category category1, String name) {
        if (checkCategory(name)) {
            for (int i = 0; i < categories.size(); i++) {
                if (categories.get(i).getName().equals(name)) {
                    categories.set(i, category1);
                }
            }
        }
    }
}