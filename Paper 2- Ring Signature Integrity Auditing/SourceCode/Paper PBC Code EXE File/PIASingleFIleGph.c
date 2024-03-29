#include <pbc.h>
#include <pbc_test.h>

int main(int argc, char **argv)
{
int i,j;
int q=70;
int n=4; // n is the number of users in the group
double time1, time2;
pairing_t pairing;
pbc_demo_pairing_init(pairing, argc, argv);
if (!pairing_is_symmetric(pairing)) pbc_die("pairing must be symmetric");
//Reading file in array
i=0;
j=0;
char* filetext[100];
char line[100];
FILE *file;
file = fopen("E:\mytext.txt", "r");
while(fgets(line, sizeof line, file)!=NULL)
{//printf("%s", line);
filetext[i]=line;
i++;
}
//for (i=0 ; i<j; i++)
  //  {
//printf("\n%s", filetext[i]);
//}
fclose(file);

//File read

element_t g,A[n],X[n],gsk[n][2],grt[n],gpk[3],Y,W,temp2,temp3;
element_t Ppub,s,P,R,k,S;
element_t Did,Qid;
element_t teop1,teop2,teop4,teop5,teop6,teop7,teop8,teop9,teop10,teop11;
element_init_G1(teop2, pairing);
element_init_G1(teop4, pairing);
element_init_G1(teop5, pairing);
element_init_G1(teop7, pairing);
element_init_Zr(teop1, pairing);
element_init_GT(teop6, pairing);
element_init_GT(teop8, pairing);
element_init_GT(teop9, pairing);
element_init_GT(teop10, pairing);
element_init_GT(teop11, pairing);



mpz_t tempn3;
mpz_init(tempn3);
//gpk[0][1][2]: g1,g2,w
//gsk[0][1]:Ai [0][2]:xi

//VCKeyGen
element_init_G1(P, pairing);
element_random(P);
element_init_G1(Ppub, pairing);
element_init_G1(Qid, pairing);
element_init_G1(Did, pairing);
element_init_G1(R, pairing);
element_init_G1(S, pairing);
element_init_G1(g, pairing);
element_init_Zr(s, pairing);
element_random(s);
element_init_Zr(k, pairing);
element_random(g);
//element_printf("g %B\n", g);

element_t h[q],z[q];
element_t h1new,z1new;
for(i = 0; i < q; i++)
			{
				element_init_Zr(z[i], pairing);
				element_init_G1(h[i], pairing);
			}
element_mul_zn(Ppub, P, s);
element_init_Zr(z1new, pairing);
element_init_G2(h1new, pairing);
//Selection of z[i] and computation of h[i]
for(i = 0; i < q; i++)
			{
			    element_random(z[i]);
			//    element_printf("ZVAL %B\n",z[i] );
			    element_pow_zn(h[i],g,z[i]);
	//			element_printf("hval %B\n", h[i]);
			}
element_random(z1new);
element_pow_zn(h1new,g,z1new);
element_from_hash(Qid, "ThisisHashVal", 13);
element_mul_zn(Did, Qid, s);
//hij computaion

element_t hij[q][q];
for(i = 0; i < q; i++)
			{
				for(j = 0; j < q; j++)
                    {
						element_init_G1(hij[i][j], pairing);
                    }

			}
element_t temp1;
element_init_Zr(temp1, pairing);
for(i = 0; i < q; i++)
			{
				for(j = 0; j < q; j++)
                    {
						if(i!=j)
                            {
								element_mul(temp1,z[i],z[j]);
								element_pow_zn(hij[i][j],g,temp1);
					//			element_printf("hij %B\n", hij[i][j]);
                            }
                    }
            }
       //     element_printf("\nVCKeyGen Done\n");
//VLRKeyGen
        element_t g1,g2;
    	element_init_G2(g2, pairing);
		element_init_G1(g1, pairing);
		element_random(g2);


        element_init_same_as(g1,g2);
		element_random(g1);
	//	element_printf("g1 %B\n", g1);
	//	element_printf("g2 %B\n", g2);

		element_init_Zr(Y, pairing);
		element_random(Y);
	//	element_printf("y %B\n", Y);
        element_random(k);
        element_mul_zn(R, P, k);

		element_init_G2(W, pairing);
		element_pow_zn(W,g2,Y);
//		element_printf("w %B\n", W);

//printf("Initialized");
		for(i=0;i<n;i++)
		{
			element_init_Zr(X[i], pairing);
			element_init_G1(A[i], pairing);
			element_init_G1(gsk[i][0], pairing);
			element_init_G1(gsk[i][1], pairing);
			element_init_G1(grt[i], pairing);
			element_init_G1(gpk[0], pairing);
			element_init_G1(gpk[1], pairing);
			element_init_G1(gpk[2], pairing);
		}

		element_init_Zr(temp2, pairing);
		element_init_Zr(temp3, pairing);
//printf("Looping");
		for(i=0;i<n;i++)
			{
			    element_random(temp2);
				element_set(X[i],temp2);
				element_add(temp2,Y,temp2);
		//		printf("While");
				while((element_is0(temp2)))
					{
						element_random(temp2);
						element_add(temp2,Y,temp2);
					}
					element_set(X[i],temp2);
		//			printf("While done");
		//			element_printf("temp2 %B\n", temp2);
				element_invert(temp3,temp2);
		//		element_printf("temp3 %B\n", temp3);
		//		printf("Invreted");
				element_pow_zn(A[i],g1,temp3);
		//		element_printf("Ai %B\n", A[i]);

				element_set(gsk[i][0],A[i]);
		//		element_printf("gsk[i][0] %B\n", gsk[i][0]);

				element_set(gsk[i][1],X[i]);
		//		element_printf("gsk[i][1] %B\n", gsk[i][1]);
				element_set(grt[i],A[i]);
		//		element_printf("grt[i] %B\n", grt[i]);
			}
		element_set(gpk[0],g1);
//		element_printf("gpk[0][1] %B\n", gpk[0]);
		element_set(gpk[1],g2);
	//	element_printf("gpk[1][1] %B\n", gpk[1]);
		element_set(gpk[2],W);
		//element_printf("gpk[2][1] %B\n", gpk[2]);
//		element_printf("\nVLRKEyGen Done\n");
//VLRKeyGen Done
//VCCom Compute commitment
element_t M[q];
element_t C[q];
element_t Aux[q];
element_t tempn;
element_init_GT(tempn, pairing);
	for(i=0;i<q;i++)
	{
		element_init_G2(M[i], pairing);
		element_init_G2(C[i], pairing);
		element_init_G2(Aux[i], pairing);
	}
	for(i=0;i<q;i++)
	{
	element_random(M[i]);
	element_pow_zn(tempn,h[i],M[i]);
	element_set(C[i],tempn);
	element_set(Aux[i],M[i]);
//	element_printf("Aux %B\n", Aux[i]);
//	element_printf("M %B\n", M[i]);
	}

//	element_printf("\nVCCom Done\n");
//Hash
	element_t hashele;
	element_init_G2(hashele, pairing);
	element_from_hash(hashele, filetext, strlen(filetext));
//	element_printf("\nComputed\n");
 //   element_printf("Hashele %B\n", hashele);

//
element_t Cnew;
element_init_G2(Cnew, pairing);
	element_t Auxnew;
element_init_G2(Auxnew, pairing);
	element_t tempn1;
element_init_G2(tempn1, pairing);
//	element_printf("h1new %B\n", h1new);
	element_pow_zn(tempn1,h1new,hashele);
	element_t tempv;
	element_init_G2(tempv, pairing);
	element_set(tempv,tempn1);
	element_random(tempn1);
//	element_printf("empnew %B\n", tempn1);
	element_set(Cnew,tempn1);
	element_set(Auxnew,hashele);
//	element_printf("Auxnew %B\n", Auxnew);
//	element_printf("Cnew %B\n", Cnew);


	//VCCom Done

//VLRSign

i=3; //current modifier


 time1 = pbc_get_time();
	element_t r,mpp,ucap,vcap,c;
	element_init_Zr(r, pairing);
	element_random(r);
//	element_printf("Executing..\n");
//	element_printf("r %B\n", r);

    element_init_G2(mpp, pairing);
	element_init_G2(ucap, pairing);
	element_init_G2(vcap, pairing);

	element_random(ucap);
    element_random(vcap);

    element_t u,v;
	element_init_same_as(u,ucap);
	element_init_same_as(v,vcap);

	element_random(u);
    element_random(v);

//	element_printf("Executing..\n");
//	element_printf("u %B\n", u);
//	element_printf("v %B\n", v);
	element_init_same_as(r,mpp);
	element_t alpha;
	element_init_Zr(alpha, pairing);
	element_random(alpha);


//	element_printf("Executing..\n");
//	element_printf("alp %B\n", alpha);
element_t htme;
	element_init_G2(htme, pairing);

	element_t T1,T2;
	element_init_G2(T1, pairing);
	element_init_G2(T2, pairing);

	element_t tempnew;
	element_init_G2(tempnew, pairing);

	element_pow_zn(T1,u,alpha);
	element_pow_zn(tempnew,v,alpha);

//	element_printf("Executing..\n");
//	element_printf("tempnew %B\n", tempnew);

	element_t delsym;
	element_init_G2(delsym, pairing);

	element_mul(T2,A[i],tempnew);
	element_mul(delsym,X[i],alpha);
	element_t ralpha,rx,rdel;
	element_init_Zr(ralpha, pairing);
	element_init_Zr(rx, pairing);
	element_init_Zr(rdel, pairing);
	element_random(ralpha);
	element_random(delsym);
	element_random(r);
	element_random(rx);
	element_random(rdel);
	element_random(htme);
    element_t R1,R2,R3,p1,p2,p3,te1,te2,te3;
	element_init_G2(R1, pairing);
	element_init_G2(R2, pairing);
	element_init_G2(R3, pairing);
	element_init_GT(p1, pairing);
	element_init_GT(p2, pairing);
	element_init_GT(p3, pairing);
	element_init_G2(te1, pairing);
	element_init_G2(te2, pairing);
	element_init_G2(te3, pairing);
    element_pow_zn(R1,u,ralpha);
	element_pairing(p1,T2,g2);
	element_pow_zn(te1,p1,rx);
	element_pairing(p2,v,W);
	element_from_hash(teop1, filetext, strlen(filetext));
	element_mul_zn(teop2, P, teop1);
	element_t revn;
	element_init_G2(revn, pairing);
	element_neg(revn,ralpha);
	element_pow_zn(te2,p2,revn);
	element_to_mpz(tempn3, R);
    element_mul_mpz(teop4, Did, tempn3);
    element_add(teop5, teop4, teop2);
	element_pairing(p3,v,g2);
	element_t revn2;
	element_init_G2(revn2, pairing);
	element_neg(revn2,rdel);
	element_pow_zn(te3,p3,revn2);
	element_invert(k, k);
    element_mul_zn(S, teop5, k);
    element_t mktemp;
	element_init_G2(mktemp, pairing);
	element_mul(mktemp,te1,te2);
	element_mul(R2,mktemp,te3);
	element_t nte1,nte2;
	element_init_G2(nte1, pairing);
	element_init_G2(nte2, pairing);
    element_init_Zr(c, pairing);

	element_pow_zn(nte1,T1,rx);
	element_pow_zn(nte2,u,revn2);
	element_mul(R3,nte1,nte2);
    element_init_same_as(c,mpp);

	element_t nte3,nte4,nte5,salpha,sx,sdel;
	element_set(hashele, htme);
	element_init_G2(nte3, pairing);
	element_init_G2(nte4, pairing);
	element_init_G2(nte5, pairing);
	element_init_G2(salpha, pairing);
	element_init_G2(sx, pairing);
	element_init_G2(sdel, pairing);
	element_random(c);
	element_mul(nte3,c,alpha);
//	element_printf(" nte3 %B\n", nte3);
	element_mul(nte4,c,delsym);
//	element_printf(" nte4 %B\n", nte4);
	element_mul(nte5,c,X[i]);
//	element_printf(" nte5 %B\n", nte5);
	element_add(salpha,ralpha,nte3);
	//element_printf(" Salpha %B\n", salpha);
	element_add(sx,rx,nte5);
//	element_printf(" sx %B\n", sx);
	element_add(sdel,rdel,nte4);
//	element_printf(" sdel %B\n", sdel);

	element_t Sig[7];
	for(i = 0; i < 7; i++)
			{
				element_init_G2(Sig[i], pairing);
			}

	element_set(Sig[0], r);
	element_set(Sig[1], T1);
	element_set(Sig[2], T2);
	element_set(Sig[3], c);
	element_set(Sig[4], salpha);
	element_set(Sig[5], sx);
	element_set(Sig[6], sdel);
	time2 = pbc_get_time();
  printf("Signature generation time = %fs\n", time2 - time1);

//element_printf(" Sig[0] %B\n", Sig[0]);
//element_printf(" Sig[1] %B\n", Sig[1]);
//element_printf(" Sig[2] %B\n", Sig[2]);
//element_printf(" Sig[3] %B\n", Sig[3]);
//element_printf(" Sig[4] %B\n", Sig[4]);
//element_printf(" Sig[5] %B\n", Sig[5]);
//element_printf(" Sig[6] %B\n", Sig[6]);

//Signature Generated


//Proof generation__VCOpen
//Computing proof for file at i=4
i=4;
j=0;
element_t proofi;
element_t tempvar;
element_t premul;
element_init_GT(proofi, pairing);
element_init_GT(tempvar, pairing);
element_init_GT(premul, pairing);
element_set1(premul);
time1 = pbc_get_time();
for(j=0;j<q;j++)
	{
	    if(j!=i)
            {
                element_pow_zn(tempvar,h[j],M[j]);
                element_mul(premul,premul,tempvar);
                }
	}
element_pow_zn(proofi,premul,z[i]);
time2 = pbc_get_time();
printf("Proof generation time = %fs\n", time2 - time1);

//VCOpen Done
//VLRVerify
i=4;
int checksum=0;
element_t commitver;
element_t temp096;
element_t divans;
 time1 = pbc_get_time();
element_from_hash(teop1, filetext, strlen(filetext));
// printf("Hahs genera\n");
element_mul_zn(teop7, P, teop1);
// printf("Hahs genera1\n");
element_pairing(teop6, P, teop7);
element_pairing(teop8, Ppub, Qid);
// printf("pairinf\n");
element_to_mpz(tempn3, R);
// printf("Hahs genera2\n");
element_pow_mpz(teop9, teop8, tempn3);
// printf("Hahs genera3\n");
element_mul(teop10, teop6, teop9);
// printf("Hahs genera4\n");
element_pairing(teop11, R, S);
// printf("Hahs genera5\n");
element_t p1re,p2re;
if (!element_cmp(teop10, teop11))
    {
   // printf("valid sig\n");
    element_init_G2(commitver, pairing);
  //  printf("valid sig2\n");
    element_set(commitver,Cnew);
   // printf("valid sig3\n");
    element_init_G2(temp096, pairing);
  //  printf("valid sig4\n");
    element_pow_zn(temp096,h[i],hashele);
    element_init_G2(divans, pairing);
   // printf("valid sig5\n");
    element_div(divans,commitver,temp096);
   // printf("valid sig6\n");
    element_init_GT(p1re, pairing);
	element_init_GT(p2re, pairing);
//	printf("valid sig006\n");
    element_pairing(p1re,divans,h[i]);
  //  printf("valid sig5526\n");
	element_pairing(p2re,proofi,g);
//	printf("valid sig6\n");
	if (!element_cmp(p1re, p2re))
    {
        checksum=1;
    }
  //  printf("%d",checksum);
    if(checksum==0)
        printf("proof valid\n");
    else
    printf("proof invalid\n");

  }
else
    {
    printf("signot valid\n");
  }
time2 = pbc_get_time();
  printf("TPA Verification time = %fs\n", time2 - time1);

//Updateing dta
printf("Enter new data:\n");
char sentence[1000];
FILE *fptr;
fptr = fopen("E:\mytext.txt", "w");
if(fptr == NULL)
   {
      printf("Error!");
   }
printf("Enter data:\n");
gets(sentence);
fprintf(fptr,"%s", sentence);
fclose(fptr);
//Read file to compute commit
i=0;
j=0;
file = fopen("E:\mytext.txt", "r");
while(fgets(line, sizeof line, file)!=NULL)
{
//printf("%s", line);
filetext[i]=line;
i++;
}
fclose(file);
//Hash
i=4;
element_t newhashele;
element_init_G2(newhashele, pairing);
element_from_hash(newhashele, filetext, strlen(filetext));
element_t proofj;
element_init_GT(proofj, pairing);
element_set1(premul);
time1 = pbc_get_time();
for(j=0;j<q;j++)
	{
	    if(j!=i)
            {
                element_pow_zn(tempvar,h[j],newhashele);
                element_mul(premul,premul,tempvar);
                }
	}
j=4;
time1 = pbc_get_time();
element_pow_zn(proofj,premul,z[i]);
element_t subtemp;
element_init_G2(subtemp, pairing);
element_sub(subtemp,newhashele,hashele);
element_t R1yu;
element_init_G2(R1yu, pairing);
element_pow_zn(R1yu,h[i],subtemp);
element_t Cdash;
element_init_G2(Cdash, pairing);
element_mul(Cdash,C[i],R1yu);
element_t proofjdash;
element_init_G2(proofjdash, pairing);
if(i!=j)
	{
        element_pow_zn(tempvar,hij[j][i],subtemp);
		element_mul(proofjdash,proofj,tempvar);
	}
else
	{
	element_set(proofjdash,proofj);
	}

time2 = pbc_get_time();
  printf("proof update time = %fs\n", time2 - time1);

}
