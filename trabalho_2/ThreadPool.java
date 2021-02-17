import java.util.concurrent.ArrayBlockingQueue;
import java.util.ArrayList;

// classe responsavel por gerenciar todos os runnables (executores e metodos a serem executados)
class ThreadPool
{
	private ArrayBlockingQueue<Runnable> queue; // estrutura de fila thread-safe contendo os runnables a serem executados pelas threads
	
	private ArrayList<QuickSortWorker> runnables = new ArrayList<>(); // lista com workers executores

	// construtor
	public ThreadPool(int threadsNumber, int maxQueueTasks)
	{
		this.queue = new ArrayBlockingQueue<Runnable>(maxQueueTasks);
		
		// inicializando workers e adicionando no arraylist
		for(int i = 0; i < threadsNumber; i++)
		{
            QuickSortWorker qsw = new QuickSortWorker(this.queue);
            runnables.add(qsw);
        }
		
		// criando threads dos workers
        for(QuickSortWorker runnable : runnables)
            new Thread(runnable).start();
		
	}
	
	// adiciona runnable na fila de execucao
	public synchronized void execute(Runnable task)
	{
		try {
			if(!this.queue.offer(task))
				System.out.println("Queue is full");
		} catch(Exception err) {
			err.printStackTrace();
		} finally {
			//System.out.printf("Added task %s to queue\n", task.toString());
		}
	}
	
	// interrompe execucao de todos os workers
	public synchronized void stop()
	{
		for(QuickSortWorker runnable : runnables)
            runnable.stop();
	}
	
	
	public synchronized void waitUntilAllTasksFinished() {
        while(this.queue.size() > 0) {
            try {
                Thread.sleep(1);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
	
	
}