import java.io.IOException;

public class bstTest 
{
    public static void main(String[] args) throws IOException 
    {
        int i, num = 0;
        TBST T = new TBST(); T.draw();
        byte [] buf = new byte[80];
	    
loop:   while (true) 
        {
            System.out.println("1: Insert ");
            System.out.println("2: Delete ");
            System.out.println("3: exit");  
            System.out.print("Choice: "); 				        
            System.out.flush();
          
            int cnt = System.in.read(buf); 
            String s = new String(buf, 0, cnt - 2);
	
            if(!s.equals("")) 
                i = Integer.valueOf(s).intValue();  
            else 
                continue;
	
	    switch(i) 
            {
                case 1: System.out.print("Number to be inserted: "); 
                        System.out.flush();
                        cnt = System.in.read(buf); 
                        s = new String(buf, 0, cnt - 2);
			    
                        if(!s.equals("")) 
                            i = Integer.valueOf(s).intValue();  
                        else 
                            continue;
			    
			T.insert(i); 
			T.draw(); 
			continue;
                case 2: System.out.print("Number to be deleted: "); 
			System.out.flush();
		        cnt = System.in.read(buf); 
			s = new String(buf, 0, cnt - 2);
			    
         	        if(!s.equals("")) 
                            i = Integer.valueOf(s).intValue(); 
                        else 
                            continue;
			    
			T.delete(i); 
			T.draw(); 
			continue;
                case 3: break loop;
            } 
        }
	    
        System.exit(0);
    }
}

class TBST extends BST
{
    public void insert(int n)
    {
        TreeNode cur, pcur;
        TreeNode node = new TreeNode();
        boolean isThread = false, duplicate = false;
        node.data = n;
        cur = root;
        pcur = null;
        
        while(cur != null && isThread == false)
        {
            if(n < cur.data)
            {
                pcur = cur;
		
                if(pcur.lt == true)
                    isThread = true;
		    
                cur = cur.left;
            }
            else if(n > cur.data)
            {
                pcur = cur;
		
                if(pcur.rt == true)
                    isThread = true;
		    
                cur = cur.right;
            }
            else
            {
                duplicate = true;
                break;
            }
        }
	
        if(!duplicate)
        {
            if(root != null)
            {
                if(n < pcur.data)     // attaching a left child
                {
                    node.left = pcur.left;
                    node.right = pcur;
                    node.lt = node.rt = true;
                    pcur.left = node;
                    pcur.lt = false;
                }
                else
                {                      // attaching a right child
                    node.right = pcur.right;
                    node.left = pcur;
                    node.lt = node.rt = true;
                    pcur.right = node;
                    pcur.rt = false;
	        }
            }
            else
            {
                root = node;
            }
        }
    }

    public void delete(int n)
    {
        TreeNode cur, pcur, temp, ptemp;
	cur = root;
	pcur = null;
        while(cur != null)
	{
	    if(cur.data == n)
	        break;
	    if(n < cur.data)
	    {
	        pcur = cur;
		if(!cur.lt)
		    cur = cur.left;
	        else 
                    cur = null;
	    }
	    else
	    {
		pcur = cur;
		if(!cur.rt)
		    cur = cur.right;
		else 
                    cur = null;
            }
        }
	if(cur == root && cur.right == null && cur.left == null)
	    root = null;  
	else if(cur != null)
	{
	    if(cur.lt == false && cur.rt == false && cur.right != null && cur.left != null)  // 2 children
	    {
                temp = cur.right; ptemp = cur;
		while(temp.lt == false)
		{
		    ptemp = temp;
		    temp = temp.left;
		}
	        int d;
	        d = temp.data;
	        delete(temp.data);
	        cur.data=d;
	    }
	    else if((cur.lt == true && cur.rt == true) || (cur.lt == true && cur.right == null) || (cur.rt == true && cur.left == null))     // deleting a leaf
	    {
	        if(pcur.left == cur)
            	{
 	            pcur.left = cur.left;
		    pcur.lt = true;
                }
                else
                {
 	            pcur.right = cur.right;
		    pcur.rt = true;
                }
            }
            else if(cur.left != null && cur.lt == false) // deleting a node with a left child
	    {
                temp = cur.left;
                ptemp = cur;
                while(temp.right != null && temp.rt == false)
		{
		    ptemp = temp;
		    temp = temp.right;
		}
		if(cur == root)
		{
		    root = cur.left;
		    root.rt = false;
		    root.right = null;
	        }
		else
		{
		    temp.right = cur.right;
		    temp.rt = cur.rt;
		    ptemp = cur.left;
		    if(pcur.right == cur)
	                pcur.right = ptemp;
		    else
			pcur.left = ptemp;
                }
            }
	    else if(cur.right != null && cur.rt == false) // deleting a node with a right child
	    {
                temp = cur.right;
                ptemp = cur;
                while(temp.left != null && temp.lt == false)
		{
		    ptemp = temp;
		    temp = temp.left;
		}
		if(cur == root)
		{
		    root = cur.right;
		    root.lt = false;
		    root.left=null;
	        }
		else
		{
		    temp.left = cur.left;
		    temp.lt = cur.lt;
		    ptemp = cur.right;
		    if(pcur.left == cur)
		        pcur.left = ptemp;
		    else
			pcur.right = ptemp;
                }
            }
        }
    }
}
