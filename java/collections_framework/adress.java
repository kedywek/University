class Address{
    private TelephoneNumber telephoneNumber;
    private String city, street;

    public Address(TelephoneNumber telephoneNumberInput, String cityInput, String streetInput){
        telephoneNumber = telephoneNumberInput;
        city = cityInput;
        street = streetInput;
    }
    public String getCity(){
        return city;
    }
    public String getStreet(){
        return street;
    }
    public TelephoneNumber getTelephoneNumber(){
        return telephoneNumber;
    }
}