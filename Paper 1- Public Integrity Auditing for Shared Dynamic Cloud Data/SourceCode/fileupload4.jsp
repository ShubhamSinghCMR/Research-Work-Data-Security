<%@page import="databaseconnection.*,java.sql.*,DSA.*,java.io.*, java.security.*,java.security.spec.*"%>
<%@include file="doheader.jsp"%>
<br><br>
<%!
Connection con;
Statement stmt,stmt1,stmt2;
ResultSet rs,rs1,rs2;
String fileid,uploadfile,email;
int count;
%>
<%
String fileid = request.getParameter("fileid");
String fname = request.getParameter("fname");
String filedata = request.getParameter("filedata");
String gpukey = request.getParameter("gpukey");
String usernames = session.getAttribute("usernames").toString();

String gnm=(String)session.getAttribute("groupname");
 byte[] buffer = filedata.getBytes();
 int len = filedata.length();
con = databasecon.getconnection();
Statement st=con.createStatement();
byte[] priv=null;
byte[] pub=null;
ResultSet r=st.executeQuery("select  sk,pk from addinggroups where groupname='"+gnm+"'");
if(r.next()){
 priv=r.getBytes(1);
 pub=r.getBytes(2);
}
  
            KeyFactory keyFactory = KeyFactory.getInstance("EC","SunEC");
          EncodedKeySpec privateKeySpec = new PKCS8EncodedKeySpec(priv);
    PrivateKey gsk = keyFactory.generatePrivate(privateKeySpec);
 
    Signature dsa;
dsa = Signature.getInstance("SHA1withECDSA","SunEC");
            dsa.initSign(gsk);
			dsa.update(buffer, 0, len);
	
            byte[] realSig = dsa.sign();
	 //byte[] key = gpukey.getBytes() ;

X509EncodedKeySpec pubKeySpec = new X509EncodedKeySpec(pub);
 
            KeyFactory keyFactory1 = KeyFactory.getInstance("EC","SunEC");
            PublicKey pubKey1 = keyFactory1.generatePublic(pubKeySpec);
		 
Signature    sig1 = Signature.getInstance("SHA1withECDSA","SunEC");
            sig1.initVerify(pubKey1);
			 sig1.update(buffer, 0, len);
			 boolean verifies = sig1.verify(realSig);
 
            System.out.println("signature verifies: " + verifies);

String usernames2 = session.getAttribute("usernames2").toString();
System.out.println("usernames2"+usernames2);
PreparedStatement p=con.prepareStatement("insert into cloud values(?,?,?,?,?,?,?,?)");
p.setString(1,fileid);
p.setString(2,fname);
p.setBytes(3,buffer);
p.setBytes(4,realSig);
p.setString(5,gnm);
p.setString(6,usernames2);
p.setString(7,gpukey);
p.setBytes(8,pub);
 p.executeUpdate();


%>
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
<div align="center">
<form action="fileupload5.jsp" method="post">
<table>
<tr>
<td><font size="5">File Id</font></td>
<td><input type="text" name="fileid" value="<%=fileid%>"  readonly/></td>
</tr>
<tr></tr>
<tr>
<td><font size="5">File Name</font></td>
<td><input type="text" name="fname" value="<%=fname%>"  readonly/></td>
</tr>
<tr></tr>
<tr>
<td><font size="5">Signature</font></td>
<td><textarea name="signdata" cols="25" rows="8"><%=new String(realSig)%></textarea></td>
</tr>
<tr></tr>
<tr>
<td><font size="5">Group Public Key</font></td>
<td><input type="text" name="gpukey" value="<%=gpukey%>" readonly></td>
</tr>
<tr></tr>
<tr>
<td><font size="5">Users Secret Keys</font></td>
<td><textarea name="users" cols="20" rows="3" readonly><%=usernames2%></textarea></td>
</tr>
<tr></tr>
<tr>
<td></td>
<td align="left"><input type="submit" value="Upload file"></td>
</tr>
</table>
</form>
	</div>
<br><br>