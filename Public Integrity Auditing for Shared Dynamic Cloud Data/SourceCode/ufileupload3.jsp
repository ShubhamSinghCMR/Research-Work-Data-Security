<%@page import="databaseconnection.*,java.sql.*,RSA.*,java.io.*"%>
<%@include file="uheader.jsp"%>
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
<%
String uname = session.getAttribute("uname").toString();
%>
<%!
Connection con;
Statement stmt,stmt1,stmt2;
PreparedStatement pstmt;
ResultSet rs,rs1,rs2;
String fileid,uploadfile,email;
int count;
String encryptdata;
%>
<%
con = databasecon.getconnection();

String fileid = request.getParameter("fileid");
String fname = request.getParameter("fname");
String filedata = request.getParameter("filedata");
String groupname = session.getAttribute("grpname").toString();
String ugpubkey = request.getParameter("ugpubkey");
String asgkpubkey = session.getAttribute("asgkprikey").toString();
session.setAttribute("myfname",fname);
%>
<div align="center">
<form action="ufileupload4.jsp" method="post">
<table>
<tr>
<td><font size="5">File Id</font></td>
<td><input type="text" name="fileid" value="<%=fileid%>"  readonly/></td>
</tr>
<tr>
<td><font size="5">File Name</font></td>
<td><input type="text" name="fname" value="<%=fname%>"  readonly/></td>
</tr>
<%
pstmt = con.prepareStatement("insert into usercloud values(?,?,?,AES_ENCRYPT(?,?),?,?,?)");
pstmt.setString(1,fileid);
pstmt.setString(2,fname);
pstmt.setString(3,filedata);
pstmt.setString(4,filedata);
pstmt.setString(5,"key");
pstmt.setString(6,groupname);
pstmt.setString(7,ugpubkey);
pstmt.setString(8,uname);
int i = pstmt.executeUpdate();
if(i>0){
stmt = con.createStatement();
rs = stmt.executeQuery("select encrypdata from usercloud where groupname='"+groupname+"' and username='"+uname+"' ");
if(rs.next()){
encryptdata = rs.getString("encrypdata");
}
}
%>

<tr>
<td><font size="5">Encrypted Data</font></td>
<td><textarea name="filedata" cols="25" rows="8"><%=encryptdata%></textarea></td>
</tr>
<tr>
<td></td>
<td align="left"><input type="submit" value="Share file"></td>
</tr>
</table>
</form>
	</div>
<br><br>