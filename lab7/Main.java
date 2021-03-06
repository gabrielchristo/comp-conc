import java.util.Random;

class Global
{
    //Definindo variaveis
    public static final Integer numberProduct = 30; // limite de produtos a serem produzidos
    public static final Integer numberConsumer = 5; // total de consumidores
    public static final Integer numberProducer = 5; // total de produtores
    public static Integer currentProductCreated = 0;
	
	public static synchronized Integer getCrrtProductCreated()
	{
		return Global.currentProductCreated;
	}
	
	public static synchronized void incrementCrrtProductCreated()
	{
		Global.currentProductCreated++;
	}
}

/*
 * Classe das threads Produtoras
 */
class Producer extends Thread
{
    //Id do Produtor
    public Integer id;

    //Recurso Compartilhado
    private Buffer sharedResource;
	
	private Random random;

    //Construtor da classe
    public Producer(Integer id, Buffer sharedResource)
    {
        this.id = id;
        this.sharedResource = sharedResource;
		this.random = new Random();
    }

    //Metodo para produzir um elemento
    private synchronized Integer createProduct()
    {
        //Criando um produto
        Integer product = random.nextInt(20);

        //Atualizando o numero de produtos criados
        Global.incrementCrrtProductCreated();

        //Retornando o produto
        return product;
    }

    //Metodo executado pelas threads
    public void run()
    {
        //Produzindo os elementos necessarios
        while(Global.getCrrtProductCreated() < Global.numberProduct)
        {
            //Criando um produto
            Integer product = this.createProduct();

            //Inserindo o produto no buffer
            this.sharedResource.Insere(product);
        }
    }
}

/*
 * Classe das threads Consumidoras
 * */
class Consumer extends Thread
{
    //Id do Produtor
    public Integer id;

    //Recurso Compartilhado
    private Buffer sharedResource;

    //Construtor da classe
    public Consumer(Integer id, Buffer sharedResource)
    {
        this.id = id;
        this.sharedResource = sharedResource;
    }

    //Metodo executado pelas threads
    public void run()
    {
        // checando limite de processos e se buffer tem algum produto
        while(  Global.getCrrtProductCreated() < Global.numberProduct )
        {	
            //Pegando um produto do buffer
            Integer product = this.sharedResource.Remove();
        }
    }
}



/*
 * Classe da funçao principal
 * */
public class Main
{


    //Funcao principal
    public static void main(String[] args)
    {
        //Criando Produtores e consumidores
        Thread[] producer = new Thread[Global.numberProducer];
        Thread[] consumer = new Thread[Global.numberConsumer];

        //Criando recursos compartilhado entre as threads
        Buffer sharedResource = new Buffer();
		
		System.out.println("import Corretude");
		System.out.println("c = Corretude.CheckingModule()");
		System.out.println("c.setSize(5)");
		
		//Inicializando consumidores
        for(int indexConsumer = 0; indexConsumer < producer.length; indexConsumer++){
            consumer[indexConsumer] = new Consumer(indexConsumer,sharedResource);
			consumer[indexConsumer].start();
		}

        //Inicializando produtores
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++){
            producer[indexProducer] = new Producer(indexProducer,sharedResource);
			producer[indexProducer].start();
		}
            

        //Aguardando produtores terminarem
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
        {
            try
            {
                producer[indexProducer].join();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
                return;
            }
        }

        //Aguardando consumidores terminarem
        for(int indexConsumer = 0; indexConsumer < consumer.length; indexConsumer++)
        {
            try
            {
                consumer[indexConsumer].join();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
                return;
            }
        }

    }
}
