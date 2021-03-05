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
这种原子粒度下，如何保证程序的正确性.

这里更新一下，根据最新的只是，汇编指令级别也不是原子级别。


[How Computers Work: The CPU and Memory](https://homepage.cs.uri.edu/faculty/wolfe/book/Readings/Reading04.htm)<br>
[汇编指令是原子操作吗?](https://www.zhihu.com/question/28092666/answer/47771188?utm_medium=social&utm_oi=658626377876639744&utm_source=wechat_session&s_r=0)

q:memory order?
>这一个问题，暂时我没有更好的答案。可以先参考下面这一篇。这里面有一个特别重要的观点就是，同步点的问题。线程同步，锁机制本质是提供一个同步点。
同步点过后，可以保证所有线程都更新到同步点之后的状态。关于同步点的demo，可以参考emc item40
>
> As a result, declaring valAvailable as std::atomic ensures that our critical
ordering requirement—imptValue must be seen by all threads to change no later
than valAvailable does—is maintained.
>
>一写多读的问题就在这，常规的思路，感觉可以不用加锁。因为写之间并没有竞争(不会导致++cnt这种多写操作无法按预期完成)
但是，还是需要加锁，问题就出在这。某一个线程写完成，其余线程可能没有同步这里的信息，导致还是读取的老的值。这么做的问题在于，当多线程通信时，某一个值不可读，
该值的通信变量进行了写操作，但是其余线程无法感知，继续读取。显然，不是预期的行为

[如何理解 C++11 的六种 memory order？](https://www.zhihu.com/question/24301047/answer/1193956492?utm_medium=social&utm_oi=658626377876639744&utm_source=wechat_session&s_r=0)<br>
[一写多读到底要不要加锁?](https://www.zhihu.com/question/31325454?utm_campaign=shareopn&utm_content=group5_qusetions&utm_medium=social&utm_oi=658626377876639744&utm_source=wechat_session&s_r=0)
