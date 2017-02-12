/**
 * Created by eksor on 06.01.2017.
 */
public class MyException extends Exception {

    public String message;

    public MyException (String message){
        this.message = message;
    }

    @Override
    public String getMessage(){
        return message;
    }

}
