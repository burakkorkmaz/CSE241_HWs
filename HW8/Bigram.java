
/**
 *          Gebze Techical University
 *      Department of Computer Engineering
 *             CSE 241/505
 *      Object Oriented Programming
 *              Fall 2016
 *            Homework # 8
 *  Inheritance, Generics, Collections in Java
 *
 * Created by Burak Kağan Korkmaz on 06.01.2017.
 * StudenId: 141044041
 */
public abstract class Bigram<G> {

    public abstract void readFile(String filename) throws MyException;

    public abstract int numGrams();

    public abstract int numOfGrams(G first, G second);

    @Override
    public abstract String toString();
}
