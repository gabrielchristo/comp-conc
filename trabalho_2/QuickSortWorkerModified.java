import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.CountDownLatch;

// classe responsavel por pegar e executar as tarefas da fila
class QuickSortWorkerModified implements Runnable
{
	//private ArrayBlockingQueue queue; // estrutura de fila recebida da thread pool
	//private Thread thread; // thread atual
	//private boolean isStopped = false; // variavel auxiliar com estado de execucao da thread
	
	private final int[] elts;
	private final int first;
	private final int size;
	private final CountDownLatch numUnsorted;
	private ThreadPool threadPool;
	
	// construtor
	public QuickSortWorkerModified(int[] elts, int first, int size, CountDownLatch n)
	{
		this.elts = elts;
		this.first = first;
		this.size = size;
		
		System.out.printf("Constructor First:%d Size:%d\n", first, size);
		
		this.numUnsorted = n;
	}
	
	public void setThreadPool(ThreadPool tp)
	{
		this.threadPool = tp;
	}
	
	// metodo executado pela thread
	public void run()
	{
        //if (size == 1)
			//numUnsorted.countDown(); // liberando barreira
		
		//if (size - first == 1) {
		//	if (elts[first] > elts[first+1]){
		//		int temp = elts[first];
		//		elts[first] = elts[first+1];
		//		elts[first+1] = temp;
		//	}
		//	//reduceUnsorted(size); // Used for termination determination
		//}
		//else if (size - first  > 1) {
			
			//int pivotPosition = first + (size-first)/2;
			
			if(first >= size)
				return;
			
			int i = first, j = size, t;
			int pivotPosition = i;
			
			int temp = elts[pivotPosition];
			elts[pivotPosition] = elts[j];
			elts[j] = temp;
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
            t = elts[j]; 
            elts[j] = elts[i]; 
            elts[i] = t; 
            j--; 
            i++; 
        } 
        
        t = elts[j + 1]; 
        elts[j + 1] = elts[size]; 
        elts[size] = t; 
       
		pivotPosition = j +1;
			
			//for (int j = first; j < size; j++) {
			//	if (elts[j] <= elts[size]) {
			//		pivotPosition++;
			//		int temp = elts[pivotPosition];
			//		elts[pivotPosition] = elts[size];
			//		elts[size] = temp;
			//	}
			//}
			//numUnsorted.countDown(); // pivot in correct sorted position
			
			int newfirst1 = first;
			int newend1 = pivotPosition - 1; 
			QuickSortWorkerModified q1 = new QuickSortWorkerModified(elts, newfirst1, newend1, numUnsorted);
			q1.setThreadPool(threadPool);
			this.threadPool.execute(q1);
			QuickSort.printArray(elts);
			
			int newfirst2 = pivotPosition+1;
			int newend2 = size;
			QuickSortWorkerModified q2 = new QuickSortWorkerModified(elts, newfirst2, newend2, numUnsorted);
			q2.setThreadPool(threadPool);
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