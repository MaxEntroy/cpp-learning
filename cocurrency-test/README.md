## Basic

q:critical section(region)?
>In concurrent programming, concurrent accesses to shared resources can lead to unexpected or erroneous behavior, so parts of the program where the shared resource is accessed need to be protected in ways that avoid the concurrent access. This protected section is the critical section or critical region. It cannot be executed by more than one process at a time. Typically, the critical section accesses a shared resource, such as a data structure, a peripheral device, or a network connection, that would not operate correctly in the context of multiple concurrent accesses
>
>In a short, the program where the shared resource is concurrent access.

q:机器层面的原子操作是什么？
>这个问题困扰我一段时间，我们知道程序可以并发执行，即指令可以交替执行。那么，这些交替执行的指令，他们的最小单位是什么。
即，是否一条指令执行一半，pending，另一条指令接着执行。这种情况下，指令就不是最小机器层面的原子单位。
那么，并发编程时就需要从这个层面考虑问题。
>
>目前我看到的知识告诉我，机器层面的原子操作，就是一条指令(一条汇编指令，至于这个汇编指令和机器指令的对应关系，暂时不清楚)
这里可以参考emc的item 40，其中提到的R-M-W operations，这其中每一个回避指令是一个原子单位，所以并发编程时，需要考虑的就是
这种原子粒度下，如何保证程序的正确性

[How Computers Work: The CPU and Memory](https://homepage.cs.uri.edu/faculty/wolfe/book/Readings/Reading04.htm)