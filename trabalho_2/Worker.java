import java.util.concurrent.ArrayBlockingQueue;

// classe responsavel por pegar e executar as tarefas da fila
class Worker implements Runnable
{
	private ArrayBlockingQueue queue; // estrutura de fila recebida da thread pool
	private Thread thread; // thread atual
	private boolean isStopped = false; // variavel auxiliar com estado de execucao da thread
	
	// construtor
	public Worker(ArrayBlockingQueue queue)
	{
		this.queue = queue;
	}
	
	// metodo executado pela thread
	public void run()
	{
        this.thread = Thread.currentThread();
        
		while(!isStopped()){
            try{
                Runnable runnable = (Runnable) this.queue.take();
                runnable.run();
            } catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }

	// interrompe execucao da thread
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