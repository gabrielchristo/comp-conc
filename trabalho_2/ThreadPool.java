import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

// classe responsavel por gerenciar todos os runnables (executores e metodos a serem executados)
class ThreadPool
{
	public RunnableQueue queue; // estrutura de fila thread-safe contendo os runnables a serem executados pelas threads
	public boolean timeout = false; // informacao de timeout das threads
	public static final int maxKeepAlive = 12; // valor maximo do contador
	public static final int timerInterval = 250; // intervalo de execucao da tarefa do timer em ms
	public int keepAlive = 0; // contador de tempo sem atividade do algoritmo
	private Timer timer; // objeto timer
	private TimerTask timerTask; // tarefa de checagem de timeout
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
	
	// inicializa timer com task
	public void startTimer()
	{	
		this.timer = new Timer();
		this.timerTask = new ThreadPoolTask(this);
		this.timer.scheduleAtFixedRate(this.timerTask, 0, timerInterval); // primeira checagem logo apos chamada
																		  // depois disso a cada timerInterval ms
	}
	
	// adiciona runnable na fila de execucao
	public synchronized void execute(Runnable task)
	{
		this.queue.push(task);
		this.keepAlive = 0; // reseta keepAlive pra cada tarefa que chega na fila 
		//System.out.printf("Added task %s to queue (queue size = %d)\n", task.toString(), this.queue.size());
	}
	
	// interrompe execucao de todos os workers
	public synchronized void stop()
	{
		for(Worker w : runnables)
            w.stop();
		this.timerTask.cancel(); // parando timer
		this.timer.cancel(); // parando tarefa do timer
	}
	
}

// classe responsavel por gerenciar tempo ocioso das threads criadas e finalizar a piscina de threads
class ThreadPoolTask extends TimerTask
{
     private ThreadPool threadPool;

	 // construtor
     public ThreadPoolTask(ThreadPool threadPool)
	 {
         this.threadPool = threadPool;
     }

	 // checagem de timeout
     @Override
     public void run()
	 {
         this.threadPool.keepAlive++;
		 //System.out.printf("Current keepAlive: %d\n", this.threadPool.keepAlive);
		 
		 if(this.threadPool.keepAlive == ThreadPool.maxKeepAlive && this.threadPool.queue.size() == 0) // tempo maximo sem atividade
		 { 
			//System.out.printf("ThreadPool timeout\n");
			this.threadPool.timeout = true;
			this.threadPool.stop();
		 }
     }
}
