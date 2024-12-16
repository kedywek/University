public class DifferentVectorsLengthsException extends Exception {
    private int[] lengths;

    public DifferentVectorsLengthsException(String errorMessage, int[] lengths) {
        super(errorMessage);
        this.lengths = lengths;
    }

    public int[] getLengths() {
        return lengths;
    }
}
