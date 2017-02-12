/**
 * Created by Burak Kağan Korkmaz on 06.01.2017.
 */
public class Pair<G> {
    private G first;
    private G second;

    public Pair(G f, G s) {
        setFirst(f);
        setSecond(s);
    }

    public G getFirst() {
        return first;
    }

    public G getSecond() {
        return second;
    }

    public void setFirst(G f) {
        this.first = f;
    }

    public void setSecond(G s) {
        this.second = s;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Pair) {
            Pair<G> pair = (Pair<G>) obj;
            return this.getFirst().equals(pair.getFirst()) &&
                    this.getSecond().equals(pair.getSecond());
        }
        return false;
    }

    @Override
    public int hashCode() {
        return first.hashCode() + second.hashCode();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("First: ").append(getFirst()).append(" - Second: ").append(getSecond());
        return sb.toString();
    }
}
