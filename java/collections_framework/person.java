class Person extends TelephoneEntry {
    private String name;
    private String lastName;
    private Address address;

    public Person(String name, String lastName, Address address) {
        this.name = name;
        this.lastName = lastName;
        this.address = address;
    }

    @Override
    public String description() {
        return "Person: " + name +" " + lastName + ", Telephone: " + address.getTelephoneNumber().getCountryCode() + "-" + address.getTelephoneNumber().getLoaclNumber() + ", Adress: " + address.getCity() + ", " + address.getStreet();
    }

}