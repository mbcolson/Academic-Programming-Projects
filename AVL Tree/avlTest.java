import java.io.IOException;

public class avlTest 
{
    public static void main(String[] args) throws IOException 
    {
        int i, num = 0;
        AVL T = new AVL(); T.draw();
        byte [] buf = new byte[80];
        
loop:   while(true) 
        {
            System.out.println("1: Insert ");  
            System.out.println("2: Delete ");
            System.out.println("3: exit");  
            System.out.print("Choice: "); 
            System.out.flush();
            
            int cnt = System.in.read(buf); 
            String s = new String(buf, 0, cnt-2);
	
            if(!s.equals(""))
                i = Integer.valueOf(s).intValue();  
	    else 
                continue;
	
            switch(i) 
            {
                case 1: System.out.print("Number to be inserted: "); 
                        System.out.flush();
                        cnt = System.in.read(buf); 
                        s = new String(buf, 0, cnt-2);
		
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
                        s = new String(buf, 0, cnt-2);
         	        
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
