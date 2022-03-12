import java.time.LocalDate;
import java.util.Arrays;

public class Exercicio3{

    private LocalDate[] datas;
    private int pos;
    private int size;

    public Exercicio3(){
        this.size = 1;
        this.datas = new LocalDate[this.size];
        this.pos = 0;
    }

    private void inc_size(){
        this.size *= 2;
        this.datas = Arrays.copyOf(this.datas, this.size);
    }
    
    public void insereData(LocalDate data){
        if (this.size == this.pos+1) this.inc_size();
        this.datas[this.pos++] = data;
    }

    public LocalDate dataMaisProxima(LocalDate data){
        LocalDate dataMin = null;
        long min = Long.MAX_VALUE;

        for (int i=0; this.datas[i] != null; i++){
            long dif = Math.abs(this.datas[i].compareTo(data));
            if (dif < min){
                min = dif;
                dataMin = this.datas[i];
            }
        }

        return dataMin;
    }

    public String toString(){
        String str = "";
        for (int i=0; this.datas[i] != null; i++) str += "\n" + this.datas[i].toString();
        str += "\n";
        return str;
    }
}