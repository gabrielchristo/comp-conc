import java.util.ArrayList;

/*
* Arquivo com a implementacao de uma fila thread-safe
* */
public class RunnableQueue
{
    //Lista para armazenar elementos da fila
    private ArrayList<Runnable> queue;

    //Construtor
    public RunnableQueue()
    {
        this.queue = new ArrayList<Runnable>();
    }

    //Metodo para verificar se esta vazia
    public synchronized boolean isEmpty()
    {
        return this.queue.isEmpty();
    }

    //Metodo para inserir elemento
    public synchronized void push(Runnable newElement)
    {
        this.queue.add(newElement);
        this.notifyAll();
    }

    //Metodo para remover um elemento
    public synchronized Runnable pop()
    {
        //Verificando se a fila esta vazia
        while(this.isEmpty())
        {
            try {
                //System.out.println("Thread Bloqueada");
                this.wait();
            } catch (InterruptedException e) {
				return null;
            }
        }
		// remove e retorna primeiro elemento da lista
        return this.queue.remove(0);
    }

    //Metodo para calcular o tamanho da fila
    public synchronized int size()
    {
        return this.queue.size();
    }

    //metodo para printar elementos da fila
    public synchronized void print()
    {
        for(Runnable runnable : this.queue)
        {
            System.out.println(runnable.toString());
        }
    }
}
