import java.util.Random;
import java.util.Arrays;

// classe responsavel pela inicializacao do vetor de inteiros, thread pool e runnable do algoritmo
class QuickSort
{
	private static final int maxArrayValue = 100; // valor maximo sorteado pelo random
	private Random random; // objeto random
	public int[] array; // vetor de inteiros
	
	// construtor
	public QuickSort(int arraySize)
	{
		this.random = new Random();
		
		try {
			this.array = new int[arraySize];
		} catch(OutOfMemoryError err) {
			System.out.println("Sem memoria disponivel para alocar array desse tamanho");
			System.exit(1);
		}
		
		this.initArrayWithRandomValues();
	}
	
	// inicializa array com valores aleatorios
	void initArrayWithRandomValues()
	{
		for(int i = 0; i < this.array.length; i++)
			this.array[i] = random.nextInt(maxArrayValue);
	}
	
	// imprime os valores do array
	public void printArray()
	{
		System.out.println(Arrays.toString(this.array));
	}
	
	public static void main(String[] args)
	{
		// checando tamanho do vetor de argumentos
		if(args.length != 2){
			System.out.println("Usage: java QuickSort arraySize threadsNumber");
			System.exit(1);
		}
		
		// convertendo argumentos (strings) para inteiros
		int arraySize = Integer.parseInt(args[0]);
		int threadsNumber = Integer.parseInt(args[1]);
		
		// criando objeto thread pool
		ThreadPool threadPool = new ThreadPool(threadsNumber);
		
		// criando objeto quicksort (vai criar array de tamanho desejado)
		QuickSort qs = new QuickSort(arraySize);
		
		// imprimindo array sorteado
		//qs.printArray();
		
		// runnable principal
		AlgorithmRunnable ar = new AlgorithmRunnable(qs.array, 0, arraySize - 1, threadPool);
		
		// checando tempo de inicio da ordenacao
		long start = System.nanoTime();
		
		ar.start();
		
		while(!threadPool.getTimeout()){ 
			; // nao faz nada na thread principal enquanto algoritmo esta executando no thread pool
		}
		threadPool.stop();
		
		// checando tempo de fim da ordenacao
		long end = System.nanoTime();
		
		System.out.println("Threads finalizaram");
		
		// mostrando array ordenado
		//qs.printArray();
		
		// imprimindo tempo de execucao em segundos
		double executionTime = (end - start)/1.0E9; // segundos
		double awaitingTime = ((double)ThreadPool.timerInterval/1000) * ThreadPool.maxKeepAlive; // segundos de espera do timeout para normalizar o valor
		
		//System.out.printf("Total: %f s Keep Alive: %f s\n", executionTime, awaitingTime);
		
		System.out.printf("Tempo de execucao: %f s\n", executionTime - awaitingTime);
		
		// teste de corretude
		boolean isCorrect = true;
		for(int i = 0; i < arraySize - 1; i++)
			if(qs.array[i] > qs.array[i+1]){
				isCorrect = false;
				break;
			}
		System.out.printf(isCorrect ? "Ordenacao concluida com sucesso\n" : "Erro na ordenacao\n");
		
	}
	
}