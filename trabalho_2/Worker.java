
// classe responsavel por pegar e executar as tarefas da fila
class Worker implements Runnable
{
	private RunnableQueue queue; // estrutura de fila recebida da thread pool	
	private Thread thread; // thread atual
	private boolean isStopped = false; // variavel auxiliar com estado de execucao da thread
	
	// construtor
	public Worker(RunnableQueue queue)
	{
		this.queue = queue;
	}
	
	// metodo executado pela thread
	public void run()
	{
        this.thread = Thread.currentThread();
        
		while(!isStopped()){
			Runnable runnable = this.queue.pop();
			// se for null a fila de tarefas esta vazia
			if(runnable != null)
				runnable.run();
        }
    }
	
	// interrompe execucao da thread
    public synchronized void stop()
	{
        this.isStopped = true;
		if(this.thread != null)
			this.thread.interrupt();
    }

	// retorna se thread esta parada
    public synchronized boolean isStopped()
	{
        return isStopped;
    }
	
}