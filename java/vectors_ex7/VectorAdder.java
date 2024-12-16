import java.util.ArrayList;
import java.util.List;
import java.util.Vector;


public class VectorAdder {
    private List<Vector<Double>> vectors = new ArrayList<>();
    public VectorAdder(){
    }
    public void addVector(Vector<Double> vector) {
        vectors.add(vector);
    }
    public int compareVectorsLengths(Vector<Double> firstVector, Vector<Double> secondVector) {
        return firstVector.size() - secondVector.size();
    }   

    public void printAllVectors() {
        for (Vector<Double> vector : vectors) {
            for (Double value : vector) {
                System.out.print(value + " ");
            }
            System.out.println();
        }
    }

    public Vector<Double> sumVectors() throws DifferentVectorsLengthsException {
        Vector<Double> result = new Vector<>();
        result = vectors.get(0);
        for (int i = 1; i < vectors.size(); i++) {
            if (compareVectorsLengths(result, vectors.get(i)) != 0) {
                throw new DifferentVectorsLengthsException("Different vectors lengths", getVectorsLengths());
            }
            for (int j = 0; j < vectors.get(i).size(); j++) {
                result.set(j, result.get(j) + vectors.get(i).get(j));
            }
        }
        return result;
    }

    public int[] getVectorsLengths() {
        int[] lengths = new int[vectors.size()];
        for (int i = 0; i < vectors.size(); i++) {
            lengths[i] = vectors.get(i).size();
        }
        return lengths;
    }
}
