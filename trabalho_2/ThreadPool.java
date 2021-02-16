
import java.util.concurrent.ArrayBlockingQueue;
import java.util.ArrayList;

class ThreadPool
{
	private ArrayBlockingQueue queue; // estrutura de fila thread-safe
	private ArrayList<QuickSortWorker> runnables = new ArrayList<>(); // lista com workers

	// construtor
	public ThreadPool(int threadsNumber, int maxQueueTasks)
	{
		this.queue = new ArrayBlockingQueue(maxQueueTasks);
		
		// inicializando runnables e adicionando no arraylist
		for(int i = 0; i < threadsNumber; i++)
		{
            QuickSortWorker qsw = new QuickSortWorker(this.queue);
            runnables.add(qsw);
        }
		
		// executando runnables
        for(QuickSortWorker runnable : runnables)
		{
            new Thread(runnable).start();
        }
		
	}
	
	
	
	
	
}