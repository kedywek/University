import java.util.TreeMap;

class Collection{
    private TreeMap<TelephoneNumber, TelephoneEntry> collection;
    public Collection(){
        collection = new TreeMap<TelephoneNumber, TelephoneEntry>();
    }
    public static void main(String[] args) {
        Collection collection = new Collection();
        collection.addExamplaryPeople();
        collection.addExamplaryCompanies();
        collection.printAll();

    }
    public void add(TelephoneNumber telephoneNumber, TelephoneEntry telephoneEntry){
        if (collection.containsKey(telephoneNumber)){
            System.out.println("Telephone number already exists");
            return;
        }
        collection.put(telephoneNumber, telephoneEntry);
    }
    public void remove(TelephoneNumber telephoneNumber){
        collection.remove(telephoneNumber);
    }
    public void print(TelephoneNumber telephoneNumber){
        System.out.println(collection.get(telephoneNumber).description());
    }
    public void printAll(){
        for(TelephoneNumber telephoneNumber : collection.keySet()){
           print(telephoneNumber);
        }
    }
    public void addExamplaryPeople(){
        TelephoneNumber telephoneNumber = new TelephoneNumber(48, 123456789);
        Address address = new Address(telephoneNumber, "Warsaw", "Marszalkowska 1");
        Person person = new Person("Jan", "Kowalski", address);
        add(telephoneNumber, person);
        
        telephoneNumber = new TelephoneNumber(48, 987654321);
        address = new Address(telephoneNumber, "Cracow", "Rynek 1");
        person = new Person("Adam", "Nowak", address);
        add(telephoneNumber, person);
        
        telephoneNumber = new TelephoneNumber(48, 111222333);
        address = new Address(telephoneNumber, "Gdansk", "Dluga 1");
        person = new Person("Ewa", "Zielinska", address);
        add(telephoneNumber, person);
    }
    public void addExamplaryCompanies(){
        TelephoneNumber telephoneNumber = new TelephoneNumber(48, 444555666);
        Address address = new Address(telephoneNumber, "Warsaw", "Marszalkowska 1");
        Company company = new Company("Company1", address);
        add(telephoneNumber, company);
        
        telephoneNumber = new TelephoneNumber(48, 777888999);
        address = new Address(telephoneNumber, "Cracow", "Rynek 1");
        company = new Company("Company2", address);
        add(telephoneNumber, company);
        
        telephoneNumber = new TelephoneNumber(48, 222333444);
        address = new Address(telephoneNumber, "Poznan", "Stary Rynek 1");
        company = new Company("Company3", address);
        add(telephoneNumber, company);
    }
}

