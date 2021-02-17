import java.util.ArrayList;

// classe responsavel por gerenciar todos os runnables (executores e metodos a serem executados)
class ThreadPool
{
	private RunnableQueue queue; // estrutura de fila thread-safe contendo os runnables a serem executados pelas threads
	
	private ArrayList<Worker> runnables = new ArrayList<>(); // lista com workers executores

	// construtor
	public ThreadPool(int threadsNumber)
	{
		// criando fila de tarefas
		this.queue = new RunnableQueue();
		
		// inicializando workers e adicionando no arraylist
		for(int i = 0; i < threadsNumber; i++)
		{
            Worker w = new Worker(this.queue);
            runnables.add(w);
        }
		
		// criando threads dos workers
        for(Worker w : runnables)
            new Thread(w).start();
		
	}
	
	// adiciona runnable na fila de execucao
	public synchronized void execute(Runnable task)
	{
		this.queue.push(task); 
		//System.out.printf("Added task %s to queue\n", task.toString());
	}
	
	// interrompe execucao de todos os workers
	public synchronized void stop()
	{
		for(Worker w : runnables)
            w.stop();
	}
	
}