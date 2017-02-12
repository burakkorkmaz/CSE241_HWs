import java.io.FileInputStream; // for file reading
import java.io.FileNotFoundException;
import java.util.Scanner;   // for file reading
import java.util.HashMap;

/**
 * Created by Burak Kağan Korkmaz on 06.01.2017.
 */
public class BigramDyn<G> extends Bigram{

    private Pair<G> myPairArr[];
    private int dataType;

    public BigramDyn(int datatype){
        setDataType(datatype);
    }


    @Override
    public void readFile(String filename) throws MyException {

//        FileInputStream stream = null;
//        try {
//            stream = new FileInputStream(filename);
//            Scanner s = new Scanner(stream);
//            String content = s.nextLine();
//            int size = 1;
//            for(int i = 0; i < content.length(); ++i)
//                if(content[i] == " ")
//                    size++;
//
//            String token[] = new String[size];
//
//            for(int i = 0; content.indexOf(" ") != -1; ++i){
//                int index = content.indexOf(" ");
//                token[i] = content.substring(0,index);
//                content = content.substring(index,content.length());
//            }
//
//            System.out.println(token);
//        } catch (FileNotFoundException e) {
//            throw new MyException("The File can NOT Found!");
//        }
//        catch (Exception e) {
//            throw new MyException("An error detected -> " + e.toString());
//        }
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
    private HashMap<Pair<G>, Integer> myMap;

    @Override
    public int numGrams() {
        int count = 0;
        for (HashMap.Entry<Pair<G>, Integer> x : myMap.entrySet()){
            count += x.getValue();
        }
        return count;

    }

    @Override
    public int numOfGrams(Object first, Object second) {
        return 0;
    }

    @Override
    public String toString() {
        return null;
    }

    public int getDataType() {
        return dataType;
    }

    public void setDataType(int dataType) {
        this.dataType = dataType;
    }
}
