class AVL extends BST
{
    public void insert(int n)
    {
        TreeNode cur, pcur, pivot;
        TreeNode node = new TreeNode();
        TreeNode pB = new TreeNode();
        TreeNode pC = new TreeNode();
        TreeNode parent_pivot = new TreeNode();
        boolean duplicate = false;
        node.data = n;
        cur = root;
        pcur = null;
        pivot = root;
        parent_pivot = null;
	
        while(cur != null)
        {
            if(cur.bf != 0)
            {
                pivot = cur;
                parent_pivot = pcur;
            }
	    
            if(n < cur.data)
            {
                pcur = cur;
                cur = cur.left;
            }
            else if(n > cur.data)
            {
                pcur = cur;
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
               if(n < pcur.data)       // attach a left child
                   pcur.left = node;
               else                    // attach a right child
                   pcur.right = node;
            }
            else
                root = node;
        }
	
        if(!duplicate)
        {
            cur = pivot;
            
	     while(cur != null && cur.data != n)
            {
                if(n < cur.data)
                {
                    cur.bf++;
                    cur = cur.left;
                }
                else
                {
                    cur.bf--;
                    cur = cur.right;
                }
            }
	    
            if(pivot != null && (pivot.bf == 2 || pivot.bf == -2))
            {
                if(n < pivot.data && n < pivot.left.data)    // LL rotation
                {
	             System.out.println("LL rotation");
		     pB = pivot.left;
                    pivot.left = pB.right;
                    pB.right = pivot;
		    
                    if(parent_pivot == null)
                        root = pB;
                    else if(pivot == parent_pivot.left)
                        parent_pivot.left = pB;
                    else
                        parent_pivot.right = pB;
			
                    pivot.bf = 0;
                    pB.bf = 0;
                }
                else if(n < pivot.data && n > pivot.left.data)  // LR rotation
                {
                    pB = pivot.left;
                    pC = pB.right;
                    pivot.left = pC.right; 
                    pB.right = pC.left;
                    pC.right = pivot; 
                    pC.left = pB;
		    
                    if(parent_pivot == null) 
                        root = pC;
                    else if(pivot == parent_pivot.left) 
                        parent_pivot.left = pC;
                    else 
                        parent_pivot.right = pC;
			
                    pC.bf = 0;
                    System.out.println("LR rotation");
		    
                    if(n == pC.data)
                    {
                        pB.bf = 0;
                        pivot.bf = 0;
                    }
                    else if(n < pC.data)
                    {
			pB.bf = 0;
			pivot.bf = -1;
		    } 
		    else 
		    {
			pB.bf = 1;
			pivot.bf = 0;
        	    }
                }
                else if(n > pivot.data && n < pivot.right.data)    // RL rotation
                {
                    pB = pivot.right;
                    pC = pB.left;
                    pivot.right = pC.left; 
                    pB.left = pC.right;
                    pC.left = pivot; 
                    pC.right = pB;
		    
                    if(parent_pivot == null) 
                        root = pC;
                    else if(pivot == parent_pivot.left) 
                        parent_pivot.left = pC;
                    else 
                        parent_pivot.right = pC;
			
                    pC.bf = 0;
                    System.out.println("RL rotation");
		    
                    if(n == pC.data)
                    {
                        pB.bf = 0;
                        pivot.bf = 0;
                    }
                    else if(n < pC.data)
                    {
			pB.bf = -1;
			pivot.bf = 0;
		    } 
		    else 
		    {
			pB.bf = 0;
			pivot.bf = 1;
		    }
                }
                else if(n > pivot.data && n > pivot.right.data)    // RR rotation
                {
		     System.out.println("RR rotation");
		     pB = pivot.right;
                    pivot.right = pB.left;
                    pB.left = pivot;
		    
                    if(parent_pivot == null)
                        root = pB;
                    else if(parent_pivot.left == pivot)
                        parent_pivot.left = pB;
                    else
                        parent_pivot.right = pB;
			
                    pivot.bf = 0;
                    pB.bf = 0;
                }
            }
        }
    }
}
