## Locadora de Veículos
## Autor
<B>Guilherme Henrique Zampronio;</b></br>
Estudante de Ciência da Computação, UNESP Campus Rio Claro.
## Sobre o projeto
Este projeto foi proposto no final da disciplina <b>"Algoritmos e Técnicas de Programação I"</b>. Tal disciplina foi o primeiro contato com uma linguagem de programação na faculdade, portanto esse projeto visou demonstrar todo o conteúdo básico relacionado a programação aprendido durante toda a disciplina. Como dito anteriormente esse foi um dos meus primeiros contatos com programação e por este motivo ele está confuso e totalmente contra as normas de um código limpo, apesar de estar funcional =)</br>
Basicamente o projeto consiste em um sistema de uma locadora de veículos com diferentes funcionalidades que será explicado com um pouco mais de detalhes logo abaixo, ademais o docente avaliou esse projeto através da plataforma <b>Run.Codes</b> baseados nos casos de testes propostos pelo mesmo.

## Especificações do docente
Uma empresa de locação de veículos está contratando você para desenvolver seu sistema de locação de veículos. Segue abaixo as especificações que você deve seguir para desenvolver o sistema solicitado. Inicialmente, é necessário entender as entidades envolvidas no processo, as quais são descritas abaixo.

-   Cliente: um cliente é uma pessoa que possui nome, endereço e telefone, sendo o endereço composto por rua, número, bairro e cidade. O telefone segue o formato: 19-9- XXXX-XXXX. Um cliente ou é uma pessoa física ou uma pessoa jurídica (fazer validação). Sendo pessoa física, o que o identifica é o seu CPF (formato: XXX.XXX.XXX-XX) (chave de busca). Sendo uma pessoa jurídica, o que o identifica é o seu CNPJ (formato: XX.XXX.XXX/XXXX-XX) (chave de busca). Para facilitar, supõe-se que é possível cadastrar no máximo 15 clientes.
    
-   Carro: um carro é descrito pelas seguintes características: renavam (formato: XXXXXXXXXXX) (chave de busca), placa (formato: LLL-NNNN), marca, modelo, ano, cor e categoria. As cores possíveis são: preta (1), branca (2) e prata (3) (fazer validação). As categorias possíveis são: hatch (1), sedan (2), suv (3) e jipe (4) (fazer validação). Para facilitar, supõe-se que é possível cadastrar no máximo 10 carros.
    
-   Cada categoria de carro está associada as seguintes informações: valor da diária e pontos fidelidade. O valor da diária é baseado, portanto, na categoria do carro. Cada categoria gera um pontuação ao cliente, que poderá ser utilizada para ganhar descontos quando for realizar futuras locações. Fazer validação para a categoria informada.
    
-   Locação: uma locação é descrita pelas seguintes características: código da locação, tipo do cliente (física ou jurídica) (fazer validação), cliente (CPF ou CNPJ) (fazer validação), carro (Renavan) (fazer validação), data de retirada e data da devolução. O código deverá ser gerado automaticamente (auto incremento) e começará na numeração 1001. As datas são compotas por dia, mês e ano (exibir para o usuário no formato dd/mm/aa). Enquanto o carro não é devolvido, a data de devolução fica em 00/00/00.
    
-   Cada cliente poderá locar no máximo 5 veículos. Haverá uma matriz que armazenará, para cada cliente, seus históricos de locação. Cada célula da matriz armazena os dados de cada locação realizada por um dado cliente.

<b>Funcionalidades do programa:</b>

-    Cadastro de Cliente: cadastra um cliente. Inicialmente é necessário informar se o cliente é uma pessoa física ou jurídica (fazer validação), para então continuar o cadastro. Não pode existir mais de um cliente com o mesmo CPF/CNPJ (chave de busca).
    
-   Cadastro de Carro: cadastra um carro. Não pode existir mais de um carro com o mesmo Renavam (chave de busca). Não esqueça de validar as entradas para cor e categoria.
    
-   Cadastro de Dados da Categoria: cadastra os dados referente a uma dada categoria de carro. É necessário verificar se a categoria informada existe.
    
-   Cadastro de Locação: realiza uma locação. Como mencionado, no momento da locação a data de devolução fica em 00/00/00. Além disso, o código da locação (chave de busca) será auto incremento, como acima descrito. Note que a locação fica armazenada em um célula da matriz, acima descrita, que armazena o histórico de locação de cada cliente.
    

É necessário atualizar também o índice que guarda, para cada cliente, sua localização na matriz. É necessário checar se o cliente e o renavam informados na locação já foram previamente cadastrados, assim como se o tipo de cliente informado é válido. Além disso, é necessário checar se o renavam informado (i.e., o carro desejado) já não está sendo utilizado em uma locação em aberto (não é possível mais de um cliente locar o mesmo carro).

Caso contrário, a locação não é realizada. Para facilitar, supõe-se que um cliente só pode locar um veículo se ele não tiver nenhuma pendência, i.e., nenhuma locação em aberto (é necessário fazer a verificação).

-   Devolve Carro: informa-se se pessoa física ou jurídica e o CPF/CNPJ do cliente e realiza- se a baixa da locação. Para realizar a baixa, atualiza-se a data de devolução.

Observe, em função das regras de locação, que ele sempre tem apenas uma locação em aberto (ou não tem nenhuma devolução a ser realizada). Note que a data de devolução deve ser posterior a data de retirada (fazer validação). Caso a devolução seja realizada no mesmo dia entende-se que há um cancelamento (neste caso, é necessário remover a locação do histórico do cliente (não aparecerá em nenhuma busca futura)). Assim que o cliente devolve o carro é informado ao mesmo o valor devido. Para tanto, computa-se o número de dias que o cliente ficou com o carro e multiplica-se pelo valor da diária de acordo com a categoria do carro locado. Esse é o valor devido.

Para simplificar, considera-se que todas as operações são realizadas dentro do mesmo ano. Contudo, se o cliente já realizou locações anteriores, consulta-se a última locação realizada (anterior a atual (por ordem de cadastro)) e a pontuação adquirida de acordo com a categoria do carro locado na época. Se a categoria gera uma pontuação de 1500 pontos, por exemplo, o cliente ganha 50,00 reais de desconto no total a ser pago. Supõe-se que a cada 1000 pontos ganha-se 50,00 reais de desconto.

O limite máximo de desconto não pode exceder a 30% do valor devido, i.e., o máximo de desconto deve ser de 30% sob o valor devido.

-   Atualiza cadastro de um dado cliente: o usuário informa se deseja atualizar os dados de um cliente pessoa física ou pessoa jurídica, seu respectivo CPF/CNPJ, e, na sequência, realiza a atualização do referido campo de interesse. É possível alterar apenas telefone e endereço. Fazer validações necessárias.
    
-   Lista os dados de um dado cliente: o usuário informa se deseja os dados de um cliente pessoa física ou pessoa jurídica, seu respectivo CPF/CNPJ, e, na sequência, exibe suas informações (nome, endereço e telefone). Fazer validações necessárias.
    
-   Lista dados de uma determinada locação (código da locação, CPF/CNPJ, nome do cliente, renavam e datas): o usuário informa o código da locação e os dados da mesma são mostrados na tela. Contudo, em relação ao cliente, não basta mostrar apenas o CPF/CNPJ, mas também seu nome. Fazer validações necessárias.
    
-   Lista locações de um dado cliente (usar função da opção anterior para exibir os dados): o usuário pode optar por mostrar todas (1), as encerradas (2) ou a em aberto (3). Caso o cliente não possua nenhuma locação em uma dada opção, deve-se informar ao usuário que neste caso não há nenhuma informação cadastrada. O usuário deve informar se o cliente é uma pessoa física ou uma pessoa jurídica e seu respectivo CPF/CNPJ para realizar a busca. Fazer validações necessárias.
    
-   Lista locações em aberto: lista todas as locações em aberto, i.e., aquelas que o cliente ainda não realizou a devolução do carro (código da locação, CPF/CNPJ e nome do cliente). A listagem pode ser separada por tipo de cliente: pessoa física e pessoa jurídica (o usuário informa o tipo desejado). Fazer validações necessárias.
    
-   Frequência de locação por categoria: considerando todas as locações (em aberto ou não), listar, das mais frequentes para as menos frequentes, a frequência com que cada categoria é locada. A listagem pode ser separada por tipo de cliente: pessoa física e pessoa jurídica (o usuário informa o tipo desejado). Fazer validações necessárias.
    
-   Sair: encerra o programa.

##  Casos de teste
<b>Segue o link para download dos casos de testes propostos:</b></br>
[Casos de Teste](https://drive.google.com/file/d/1IlK0Jb5WvEoeZ5KB8QWdl4-c894t6TXY/view?usp=sharing)

### Linguagem Utilizada : C
