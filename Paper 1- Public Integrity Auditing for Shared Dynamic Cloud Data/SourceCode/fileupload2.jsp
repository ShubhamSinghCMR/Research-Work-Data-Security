<%@page import="databaseconnection.*,java.sql.*,RSA.*,java.io.*"%>
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

con = databasecon.getconnection();

%>
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
<div align="center">
<form action="fileupload3.jsp" method="post">
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
<td><font size="5">File Data</font></td>
<td><textarea name="filedata" cols="25" rows="8"><%=filedata%></textarea></td>
</tr>
<tr></tr>
<tr>
<td><font size="5">Select Group</font></td>
<td><select name="gname" required><option value="">Select Group</option>
<%
stmt = con.createStatement();

rs = stmt.executeQuery("select groupname from addinggroups");
while(rs.next()){
%>
<option value="<%=rs.getString("groupname")%>"><%=rs.getString("groupname")%></option>
<%
	}
%>
</select></td>
</tr>
<tr></tr>
<tr>
<td></td>
<td align="left"><input type="submit" value="Continue"></td>
</tr>
</table>
</form>
	</div>
<br><br>