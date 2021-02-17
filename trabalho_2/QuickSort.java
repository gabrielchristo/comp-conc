import java.util.Random;
import java.util.Arrays;
import java.util.concurrent.CountDownLatch;

// classe responsavel pela inicializacao do vetor de inteiros e thread pool
class QuickSort
{
	private static final int maxArrayValue = 50; // valor maximo sorteado pelo random
	private Random random; // objeto random
	public int[] array; // vetor de inteiros
	
	// construtor
	public QuickSort(int arraySize)
	{
		this.random = new Random();
		this.array = new int[arraySize];
		this.initArrayWithRandomValues();
	}
	
	// inicializa array com valores aleatorios
	void initArrayWithRandomValues()
	{
		for(int i = 0; i < this.array.length; i++)
			this.array[i] = random.nextInt(maxArrayValue);
	}
	
	// imprime os valores do array
	public static void printArray(int[] array)
	{
		System.out.println(Arrays.toString(array));
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
		// alocamos o vetor de tarefas com o pior caso possivel de ordenacao: n^2 ??????????????????????
		ThreadPool threadPool = new ThreadPool(threadsNumber, arraySize * arraySize);
		
		// criando objeto quicksort (vai criar array de tamanho desejado)
		QuickSort qs = new QuickSort(arraySize);
		
		// imprimindo array sorteado
		QuickSort.printArray(qs.array);
		
		// checando tempo de inicio da ordenacao
		long start = System.currentTimeMillis();
		
		// runnable principal
		QuickSortWorkerModified qswm = new QuickSortWorkerModified(qs.array, 0, arraySize - 1, threadPool);
		qswm.sort();
		
		//threadPool.waitUntilAllTasksFinished();
		//threadPool.stop();
		
		// checando tempo de fim da ordenacao
		long end = System.currentTimeMillis();
		System.out.printf("Elapsed time: %d ms\n", end - start);
		
		// mostrando array ordenado
		QuickSort.printArray(qs.array);
		
		
	}
	
	
	
}