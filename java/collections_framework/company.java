class Company extends TelephoneEntry {
    private String companyName;
    private Address address;

    public Company(String companyName, Address address) {
        this.companyName = companyName;
        this.address = address;
    }

    @Override
    public String description() {
        return "Company: " + companyName + ", Telephone: " + address.getTelephoneNumber().getCountryCode() + "-" + address.getTelephoneNumber().getLoaclNumber() + ", Adress: " + address.getCity() + ", " + address.getStreet();
    }
}