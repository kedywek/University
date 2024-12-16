import java.util.ArrayList;
import java.util.List;

public class Category {
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
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).getName().equals(name)) {
                    items.set(i, item1);
                }
            }
        }
    }

    public void removeItem(String item) {
        if (checkItem(item)) {
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).getName().equals(item)) {
                    items.remove(i);
                }
            }
        }
    }

    public boolean checkItem(String name) {
        for (int i = 0; i < items.size(); i++) {
            if (items.get(i).getName().equals(name)) {
                return true;
            }
        }
        return false;
    }
}