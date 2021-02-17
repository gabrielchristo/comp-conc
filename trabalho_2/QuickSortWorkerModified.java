import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.CountDownLatch;

// classe responsavel por pegar e executar as tarefas da fila
class QuickSortWorkerModified implements Runnable
{
	//private ArrayBlockingQueue queue; // estrutura de fila recebida da thread pool
	private Thread thread; // thread atual
	//private boolean isStopped = false; // variavel auxiliar com estado de execucao da thread
	
	private final int[] elts;
	private final int first;
	private final int size;
	//private final CountDownLatch numUnsorted;
	private ThreadPool threadPool;
	
	// construtor
	public QuickSortWorkerModified(int[] elts, int first, int size, ThreadPool threadPool)
	{
		this.elts = elts;
		this.first = first;
		this.size = size;
		
		System.out.printf("Constructor First:%d Size:%d\n", first, size);
		
		this.threadPool = threadPool;
	}
	
	// troca dois elementos de lugar em um vetor de inteiros
	public synchronized void swap(int[] array, int i, int j)
	{
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}


	
	// todo snapshow method
	
	public void setThreadPool(ThreadPool tp)
	{
		//this.threadPool = tp;
	}
	
	// metodo executado pela thread
	public void run()
	{
		
		this.thread = Thread.currentThread();
		System.out.printf("Thread %s\n", this.thread.toString());
		
			
			// escolhendo elemento central como pivo
			int pivotPosition = first + (size-first)/2;
			
			if(first >= size)
				return;
			
			int i = first, j = size;
			
			this.swap(elts, pivotPosition, j);
			j--;
			
			while (i <= j) { 
            if (elts[i] <= elts[size]) { 
                i++; 
                continue; 
            } 
            if (elts[j] >= elts[size]) { 
                j--; 
                continue; 
            } 
			
			// swap
			this.swap(elts, i, j);
            j--; 
			
            i++; 
        } 
        
		
		// voltando pivo para posicao original
		this.swap(elts, j+1, size);
       
		pivotPosition = j +1;
			
			int newfirst1 = first;
			int newend1 = pivotPosition - 1; 
			QuickSortWorkerModified q1 = new QuickSortWorkerModified(elts, newfirst1, newend1, this.threadPool);
			
			this.threadPool.execute(q1);
			QuickSort.printArray(elts);
			
			int newfirst2 = pivotPosition+1;
			int newend2 = size;
			QuickSortWorkerModified q2 = new QuickSortWorkerModified(elts, newfirst2, newend2, this.threadPool);
			
			this.threadPool.execute(q2);
			QuickSort.printArray(elts);
		
		//}
		 
    }

	// interrompe execucao da thread
    public void sort()
	{
        threadPool.execute(this);

		//try{numUnsorted.await();}
		//catch(Exception e){e.printStackTrace();}
		
    }

	
	
}