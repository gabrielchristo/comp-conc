
import java.util.concurrent.ArrayBlockingQueue;

class QuickSortWorker implements Runnable
{
	private ArrayBlockingQueue queue; // estrutura de fila thread-safe
	private Thread thread;
	private boolean isStopped = true;
	
	public QuickSortWorker(ArrayBlockingQueue queue)
	{
		this.queue = queue;
	}
	
	// metodo executado pela thread
	public void run(){
        this.thread = Thread.currentThread();
        this.stop();
		
		// todo: quicksort
		// vai pegar dados da fila e fazer o tratamento
    }

	// para execucao da thread
    public synchronized void stop()
	{
        this.isStopped = true;
        this.thread.interrupt();
    }

	// retorna se thread esta parada
    public synchronized boolean isStopped()
	{
        return isStopped;
    }
	
}