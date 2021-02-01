
/*
 * Classe das threads Produtoras
 */
class Producer extends Thread
{
    //Id do Produtor
    public Integer id;

    //Recurso Compartilhado
    private Buffer sharedResource;

    //Construtor da classe
    public Producer(Integer id, Buffer sharedResource)
    {
        this.id = id;
        this.sharedResource = sharedResource;
    }

    //Metodo para produzir um elemento
    private synchronized Integer createProduct(Integer idProduct)
    {
        //Criando um produto
        Integer product = 1; // todo: create random number

        //Atualizando o numero de produtos criados
        this.sharedResource.updateCurrentNumberProduct();

        //Retornando o produto
        return product;
    }

    //Metodo executado pelas threads
    public void run()
    {
        //Iniciando a thread
        System.out.printf("Thread Produtora %d iniciada\n", this.id);

        //Produzindo os elementos necessarios
        while(this.sharedResource.getCurrentNumberProduct() != this.sharedResource.numberTotalProduct)
        {
            //Criando um produto
            Integer product = this.createProduct(this.sharedResource.getCurrentNumberProduct());

            //Inserindo o produto no buffer
            this.sharedResource.insert(product);
        }

        //Encerrando a thread
        System.out.printf("Thread Produtora %d finalizada\n", this.id);
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

    //Metodo para processar o produto
    private void processesProduct(Integer product)
    {
        //Printando o produto
        System.out.printf("Mostrando Int: %d\n", product);
    }

    //Metodo executado pelas threads
    public void run()
    {
        //Iniciando a thread
        System.out.printf("Thread Consumidora %d iniciada\n", this.id);

        //Processando os elementos necessarios
        while((this.sharedResource.getCurrentNumberProduct() != this.sharedResource.numberTotalProduct)
        && (!this.sharedResource.isEmpty()))
        {
            //Pegando um produto do buffer
            Integer product = this.sharedResource.remove();

            //Processando o produto
            this.processesProduct(product);
        }

        //Encerrando a thread
        System.out.printf("Thread Consumidora %d finalizada\n", this.id);
    }
}



/*
* Classe da funçao principal
* */
public class Main
{
    //Definindo variaveis
    static final Integer numberProduct = 30; // limite de produtos a serem produzidos
    static final Integer numberConsumer = 5; // total de consumidores
    static final Integer numberProducer = 5; // total de produtores
    static final Integer sizeBuffer = 4; // tamanho do buffer

    //Funcao principal
    public static void main(String[] args)
    {
        //Criando Produtores e consumidores
        Thread[] producer = new Thread[numberProducer];
        Thread[] consumer = new Thread[numberConsumer];

        //Criando recursos compartilhado entre as threads
        Buffer sharedResource = new Buffer(sizeBuffer,numberProduct);

        //Inicializando produtores
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
            producer[indexProducer] = new Producer(indexProducer,sharedResource);

        //Inicializando consumidores
        for(int indexConsumer = 0; indexConsumer < producer.length; indexConsumer++)
            consumer[indexConsumer] = new Consumer(indexConsumer,sharedResource);

        //Iniciando a execucao dos produtores
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
            producer[indexProducer].start();

        //Iniciando a execucao dos consumidores
        for(int indexConsumer = 0; indexConsumer < producer.length; indexConsumer++)
            consumer[indexConsumer].start();

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
