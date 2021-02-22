
// classe responsavel por pegar e executar as tarefas da fila
class AlgorithmRunnable implements Runnable
{
	private Thread thread; // thread atual
	private int[] array; // array de inteiros a ser ordenado
	private int first; // primeiro indice do subarray atual
	private int last; // ultimo indice do subarray atual
	private ThreadPool threadPool; // instancia de thread pool para spawn de novas tarefas
	
	// construtor
	public AlgorithmRunnable(int[] array, int first, int last, ThreadPool threadPool)
	{
		this.array = array;
		this.first = first;
		this.last = last;
		this.threadPool = threadPool;
	}
	
	// inicializa recursao
    public void start()
	{
		System.out.println("Ordenando");
		threadPool.startTimer();
        threadPool.execute(this);
    }
	
	// troca dois elementos de lugar em um vetor de inteiros
	public synchronized void swap(int[] array, int i, int j)
	{
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		threadPool.resetKeepAlive(); // resetando keepAlive a cada operacao de swap
	}
	
	// metodo executado pela thread
	public void run()
	{
		// variavel com a thread atual (criada pelo thread pool)
		this.thread = Thread.currentThread();	
		
		// escolhendo elemento central como pivo
		int pivot = first + (last - first)/2;
			
		// checando indices para saber hora de finalizar a recursao
		if(first >= last){
			this.threadPool.resetKeepAlive();
			return;
		}
		
		// definindo variaveis auxiliares
		int i = first, j = last;
		
		// trocando pivo com elemento array[last]
		this.swap(array, pivot, j);
		j--;
			
		// particionando array em elementos menores/maiores que o pivo
		while (i <= j) { 
            if (array[i] <= array[last]) { 
                i++; 
                continue; 
            } 
            if (array[j] >= array[last]) { 
                j--; 
                continue; 
            } 
			
			// swap se for necessario
			this.swap(array, i, j);
            j--; 
			
			// incrementando indice i
            i++; 
        }
        
		// voltando pivo para posicao original
		this.swap(array, j + 1, last);
		pivot = j + 1; 
		
		// novo runnable para elementos a esquerda do pivo
		AlgorithmRunnable left = new AlgorithmRunnable(array, first, pivot - 1, this.threadPool);
		this.threadPool.execute(left);
		
		// novo runnable para elementos a direita do pivo		
		AlgorithmRunnable right = new AlgorithmRunnable(array, pivot + 1, last, this.threadPool);
		this.threadPool.execute(right);
		
		this.threadPool.resetKeepAlive();
		 
    }
	
}