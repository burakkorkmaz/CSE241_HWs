import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Created by Burak Kağan Korkmaz on 06.01.2017.
 * StudentId : 141044041
 */
public class BigramMap<G> extends Bigram<G> {

    private HashMap<Pair<G>, Integer> myMap;
    private int dataType;

    public BigramMap(int datatype) {
        setDataType(datatype);
    }

    @Override
    public void readFile(String filename) throws MyException {
        try {
            FileInputStream stream = new FileInputStream(filename);
            Scanner s = new Scanner(stream);
            String content = s.nextLine();
//            System.out.println(content);
            String[] strArr = content.split(" ");
            G arr[] = (G[]) strArr;

            //System.out.println("Generic Object Type:"+arr.getClass().getTypeName());

            if (arr.length <= 1)
                throw new MyException("Insufficient element for a bigram!\\n");

            myMap = new HashMap<>();

            for (int i = 0; i < arr.length - 1; ++i) {
                if (myMap.isEmpty()) {
                    myMap.put(new Pair<G>(arr[i], arr[i + 1]), 1);
                    //System.out.println("Add first element");
                } else {
                    Pair<G> pr = new Pair<G>(arr[i], arr[i + 1]);
                    if (myMap.containsKey(pr)) {
                        //System.out.println("Map has same element key");
                        myMap.put(pr, myMap.get(pr) + 1);
                    } else {
                        //System.out.println("Element was added");
                        myMap.put(new Pair<G>(arr[i], arr[i + 1]), 1);
                    }
                }
            }
//            System.out.println("MapSize:" + myMap.size() + " ArraySize: " + arr.length);


        } catch (FileNotFoundException e) {
            throw new MyException("The File can NOT Found!");
        } catch (Exception e) {
            throw new MyException("An error detected -> " + e.toString());
        }
    }

    @Override
    public int numGrams() {
        int count = 0;
        for (Map.Entry<Pair<G>, Integer> x : myMap.entrySet()){
            count += x.getValue();
        }
        return count;
    }

    @Override
    public int numOfGrams(G first, G second) {
        Pair<G> p = new Pair<G>(first,second);
        for (Map.Entry<Pair<G>, Integer> x : myMap.entrySet()){
            if(x.getKey().equals(p)){
                return x.getValue();
            }
        }
        return 0;
    }

    @Override
    public String toString() {
        String s = "";
        for (Map.Entry<Pair<G>, Integer> x : myMap.entrySet()) {
            Pair<G> key = x.getKey();
            Integer value = x.getValue();
            s += (key.getFirst() + " " + key.getSecond() +
                    " -> " + value + "\n");
        }
        return s.toString();
    }

    public void setDataType(int dataType) {
        this.dataType = dataType;
    }

    public int getDataType() {
        return dataType;
    }


}
