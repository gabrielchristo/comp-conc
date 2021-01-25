/*
 * Classe para modelar um vetor
 */
class Vector{
    //Campo para vetor da classe
    private Integer[] vector;

    //Tamanho do vetor
    private Integer sizeVector;


    //Construtor
    public Vector(Integer sizeVector) {
        this.vector = new Integer[sizeVector];
        this.sizeVector = sizeVector;
    }

    //Método para pegar o valor de um elemento do vetor dado seu indice
    public Integer getElementVector(int index) {
        return this.vector[index];
    }

    //Metodo para setar elemento dentro do vetor
    public synchronized void setElementVector(int index, Integer element) {
        this.vector[index] = element;
    }

    //Metodo para pegar o tamanho dos elementos
    public Integer getSizeVector()
    {
        return this.sizeVector;
    }

    //Metodo para printar vetor
    public void print()
    {
        //Mensagem inicial
        System.out.println("============================== Inicio Print ====================================");

        //Percorrendo vetor
        for(Integer element : this.vector)
            System.out.println(element);

        //Mensagem final
        System.out.println("============================== Final Print =================================\n\n");
    }

}

/*
 * Classe para realizar a execução concorrente da soma de vetores
 */
class ThreadVector extends Thread
{
    //Id da thread
    Integer id;

    //Quantidade total de threads
    Integer numberThreads;

    //Campo para o recurso compartilhado pelas threads
    private SharedResource vectors;

    //Construtor
    public ThreadVector(SharedResource vectors, Integer id, Integer numberThreads)
    {
        this.id = id;
        this.numberThreads = numberThreads;
        this.vectors = vectors;
    }

    //Funcao executada pelas threads
    public void run()
    {
        //Percorrendo os indices apropriados para cada thread
        Integer sizeVector = this.vectors.getVectorResult().getSizeVector();
        for(int index = this.id; index < sizeVector; index+=this.numberThreads)
        {
            this.vectors.sumElement(index);
        }
    }
}



/*
 * Classe para armazenar os vetores envolvidos na soma
 */
class SharedResource
{
    //Vetor parcela da soma a
    private Vector vectorPortionA;

    //Vetor parcela da soma b
    private Vector vectorPortionB;

    //Vetor resultado da soma
    private Vector vectorResult;

    //Construtor
    public SharedResource(Integer sizeVector)
    {
        //Criando vetores
        this.vectorPortionA = new Vector(sizeVector);
        this.vectorPortionB = new Vector(sizeVector);
        this.vectorResult = new Vector(sizeVector);
    }

    //Getter para vetor a
    public Vector getVectorPortionA()
    {
        return this.vectorPortionA;
    }

    //Getter para vetor a
    public Vector getVectorPortionB()
    {
        return this.vectorPortionB;
    }

    //Getter para vetor a
    public Vector getVectorResult()
    {
        return this.vectorResult;
    }

    //Metodo para realizar a soma
    public synchronized void sumElement(int index)
    {
        //Pegando a soma do elemento
        Integer sum = this.vectorPortionA.getElementVector(index) + this.vectorPortionB.getElementVector(index);

        //Setando elemento no vetor de resultado
        this.vectorResult.setElementVector(index,sum);
    }
}


/*
 * Classe com a função principal
 */
public class Main
{
    //Definindo variaveis
    static final Integer sizeVector = 10;
    static final Integer numberThreads = 2;

    public static void fillsVector(Vector vector)
    {
        for(int index = 0; index < vector.getSizeVector(); index++)
            vector.setElementVector(index,index);

    }

    //Funcao Principal
    public static void main(String[] args)
    {
        //Criando vetor de threads
        Thread[] threads = new Thread[numberThreads];

        //Criando vetores para a soma
        SharedResource vectors = new SharedResource(sizeVector);

        //Preenchendo vetores parcela
        fillsVector(vectors.getVectorPortionA());
        fillsVector(vectors.getVectorPortionB());

        //Printando vetores
        vectors.getVectorPortionA().print();
        vectors.getVectorPortionB().print();

        //Inicializando vetor de threads
        for(int indexThread = 0; indexThread < numberThreads; indexThread++)
            threads[indexThread] = new ThreadVector(vectors,indexThread,numberThreads);

        //Executando soma concorrente
        for(Thread thread : threads)
            thread.start();

        //Garntindo que todas as threads terminarão
        for(Thread thread : threads)
        {
            try
            {
                thread.join();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }

        //Prinatando vetor de resultado da soma
        vectors.getVectorResult().print();
    }
}
