* 反编译并将结果输出到bomb.s文件：
objdump -D bomb > bomb.s
* phase_1
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    $0x8,%rsp
  400ee4:	be 00 24 40 00       	mov    $0x402400,%esi
  400ee9:	e8 4a 04 00 00       	callq  401338 <strings_not_equal>
  400eee:	85 c0                	test   %eax,%eax
  400ef0:	74 05                	je     400ef7 <phase_1+0x17>
  400ef2:	e8 43 05 00 00       	callq  40143a <explode_bomb>
  400ef7:	48 83 c4 08          	add    $0x8,%rsp
  400efb:	c3    
<strings_not_equal>是判断两字符串是否相等，若相等则eax=0，若不相等则eax=1。即%esi和%rdi的比较。%rdi就是我们需要输入的字符串，%esi是通关字符串。

* phase_2
400efc-> 400f30 ->
0000000000400efc <phase_2>:
  400efc:	55                   	push   %rbp
  400efd:	53                   	push   %rbx
  400efe:	48 83 ec 28          	sub    $0x28,%rsp
  400f02:	48 89 e6             	mov    %rsp,%rsi
  400f05:	e8 52 05 00 00       	callq  40145c <read_six_numbers>
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp)          //rsp是栈顶指针，(%rsp)放的是第1个参数，所以(%rsp) = 0x1
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	callq  40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax      //eax是rbx前一个参数值的低32位
  400f1a:	01 c0                	add    %eax,%eax            //eax值乘以2
  400f1c:	39 03                	cmp    %eax,(%rbx)          
  400f1e:	74 05                	je     400f25 <phase_2+0x29>//判断eax和rbx是否相等，所以后一个参数值rbx应该是前一个参数值eax的2倍
  400f20:	e8 15 05 00 00       	callq  40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx            //若相等，%rbx地址+4，让rbx指向后一个参数
  400f29:	48 39 eb             	cmp    %rbp,%rbx            //循环完第6个参数
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx      //0x4(%rsp)表示第2个参数地址，所以此时rbx是第2个参数值
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp     //0x18(%rsp)是第6个参数末尾地址，所以rbp是第6个参数的末尾
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	retq   