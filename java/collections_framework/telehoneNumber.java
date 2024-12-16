class TelephoneNumber implements Comparable<TelephoneNumber>{
    private int countryCode;
    private int loaclNumber;
    TelephoneNumber( int countryCodeInput,  int loaclNumberInput){
        if (countryCodeInput < 0 || loaclNumberInput < 0){ 
            throw new IllegalArgumentException("Country code and local number must be positive numbers");
            
        }
        countryCode = countryCodeInput;
        loaclNumber = loaclNumberInput;
    }
    public int getCountryCode() {
        return countryCode;
    }
    public long getLoaclNumber() {
        return loaclNumber;
    }
    @Override public int compareTo(TelephoneNumber secodTelephonNumber){
        if(this.countryCode != secodTelephonNumber.countryCode){
            return this.countryCode - secodTelephonNumber.countryCode;
        }
        else{
            return this.loaclNumber - secodTelephonNumber.loaclNumber;
        }
    }
}