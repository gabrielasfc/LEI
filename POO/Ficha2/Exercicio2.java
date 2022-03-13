public class Exercicio2{
    
    private int[][] pauta;
    int nAlunos, nUC;

    public Exercicio2(){
        this.pauta = new int[5][5];
        this.nAlunos = 5;
        this.nUC = 5;
    }

    public void atualizaPauta(int aluno, int uc, int nota){
        this.pauta[aluno][uc] = nota;
    }

    public int somaNotasUC(int uc){
        int soma = 0;
        for (int i=0; i < this.nAlunos; i++) soma += this.pauta[i][uc];

        return soma;
    }

    public float mediaAluno(int aluno){
        float media = 0;
        for (int nota : this.pauta[aluno]) media += nota;
        media /= this.nUC;

        return media;
    }

    public float mediaUC(int uc){
        float media = 0;
        for (int i=0; i < this.nAlunos; i++) media += this.pauta[i][uc];
        media = media / this.nAlunos;

        return media;
    }

    public int notaMax(){
        int max = Integer.MIN_VALUE;

        for (int[] alunos : this.pauta){
            for (int nota : alunos){
                if (nota > max) max = nota;
            }
        }

        return max;
    }

    public int notaMin(){
        int min = Integer.MAX_VALUE;

        for (int[] alunos : this.pauta){
            for (int nota : alunos){
                if (nota  < min) min = nota;
            }
        }

        return min;
    }

    public int[] notasAcima(int lim){
        int[] aux = new int[this.nAlunos * this.nUC];
        int ind = 0;

        for (int[] aluno : this.pauta){
            for (int nota : aluno){
                if (nota > lim) aux[ind++] = nota;
            }
        }
        
        int[] res = new int[ind];
        System.arraycopy(aux, 0, res, 0, ind);

        return res;
    }

    public String printPauta(){
        String str = new String("");

        for (int i = 0; i < this.nAlunos; i++){
            String aux = "\n---Aluno " + i + "---\n";
            for (int j = 0; j < this.nUC; j++){
                aux += "UC " + j + ": " + this.pauta[i][j] + " | ";
            }
            str += aux += "\n";
        }

        str += "\n";
        return str;
    }

    public int indUCMediaMax(){
        int indMax = Integer.MIN_VALUE;
        float max = Integer.MIN_VALUE;
        float media = 0;

        for (int i=0; i < this.nUC; i++){
            if ((media = this.mediaUC(i)) > max){
                indMax = i;
                max = media;
            }
        }

        return indMax;
    }
}
