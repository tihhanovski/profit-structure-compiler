unit RiikBL;

//RIIGID
//Generated automatically.
//Date: 04.05.2020 14:10:08

interface
uses Classes, MiscFuncs, ProfitObject, DB, IBSQL, SysUtils, Variants;

type
    TRiik = class(TProfitObject)
    private
    protected
    public
        id: Integer;
        kood: String;
        nimi: String;
        seletus: String;
        eukood: String;

        constructor Create; override;
        procedure Clear; override;
        function doLoad: Boolean; override;
        function doSave: Boolean; override;
        function GetDeleteSql: String; override;
        function InnerCanDelete: Boolean; override;
        function IsUnique: Boolean; override;
        function RegID: Integer; override;
        function FieldCount: Integer; override;
        function GetFieldValue(i: Integer): Variant; overload; override;
        procedure SetFieldValue(i: Integer; val: Variant); overload; override;
        function GetFieldValue(s: String): Variant; overload; override;
        procedure SetFieldValue(s: String; val: Variant); overload; override;
        function GetFieldSize(i: Integer): Integer; overload; override;
        function GetFieldSize(s: String): Integer; overload; override;
        function GetFieldName(i: Integer): String; override;
        function GetFieldTypeName(i: Integer): String; override;
        function IsFieldOnUI(i: Integer): Boolean; override;
        function GetUIControlTypeName(i: Integer): String; override;
        function GetFieldObjectTypeName(i: Integer): String; overload; override;
        procedure GetRplCascades(sl: TStringList); override;
        function DeleteCascades(bSoft: Boolean = true): Boolean; override;
        function doReplicationPost: Boolean; override;
        function IsReplicationExists: Boolean; override;
        procedure ClearReplicationSchedule; override;
        function getDBTable: String; override;

        //Non-standard public methods:
        function LoadByKNKood(s: String): Boolean;
    end;

implementation

constructor TRiik.Create;
begin
    Clear;
    inherited Create;
end;

function TRiik.getDBTable: String;
begin
    Result := 'RIIGID';
end;

function TRiik.GetFieldName(i: Integer): String;
begin
    case i of
        0: Result := 'id';
        1: Result := 'kood';
        2: Result := 'nimi';
        3: Result := 'seletus';
        4: Result := 'eukood';
        else Result := '';
    end;
end;

function TRiik.GetFieldTypeName(i: Integer): String;
begin
    case i of
        0: Result := 'Integer';
        1: Result := 'String';
        2: Result := 'String';
        3: Result := 'String';
        4: Result := 'String';
        else Result := '';
    end;
end;

function TRiik.GetFieldObjectTypeName(i: Integer): String;
begin
    case i of
        0: Result := '';
        1: Result := '';
        2: Result := '';
        3: Result := '';
        4: Result := '';
        else Result := '';
    end;
end;

procedure TRiik.SetFieldValue(s: String; val: Variant);
var
    s1: String;
begin
    s1 := Trim(AnsiLowerCase(s));
    if s1 = 'id' then
        id := Integer(val);
    if s1 = 'kood' then
        kood := String(val);
    if s1 = 'nimi' then
        nimi := String(val);
    if s1 = 'seletus' then
        seletus := String(val);
    if s1 = 'eukood' then
        eukood := String(val);
end;

function TRiik.GetFieldValue(s: String): Variant;
var
    s1: String;
begin
    Result := null;
    s1 := Trim(AnsiLowerCase(s));
    if s1 = 'id' then
        Result := id;
    if s1 = 'kood' then
        Result := kood;
    if s1 = 'nimi' then
        Result := nimi;
    if s1 = 'seletus' then
        Result := seletus;
    if s1 = 'eukood' then
        Result := eukood;
end;

function TRiik.GetFieldSize(s: String): Integer;
var
    s1: String;
begin
    Result := 0;
    s1 := Trim(AnsiLowerCase(s));
    if s1 = 'id' then
        Result := 0;
    if s1 = 'kood' then
        Result := 20;
    if s1 = 'nimi' then
        Result := 100;
    if s1 = 'seletus' then
        Result := 1000;
    if s1 = 'eukood' then
        Result := 2;
end;

procedure TRiik.SetFieldValue(i: Integer; val: Variant);
begin
    case i of
        0: id := Integer(val);
        1: kood := String(val);
        2: nimi := String(val);
        3: seletus := String(val);
        4: eukood := String(val);
    end;
end;

function TRiik.IsFieldOnUI(i: Integer): Boolean;
begin
    case i of
        0: Result := false;
        1: Result := false;
        2: Result := false;
        3: Result := false;
        4: Result := false;
    else Result := false;
    end;
end;

function TRiik.GetUIControlTypeName(i: Integer): String;
begin
    case i of
        0: Result := '';
        1: Result := '';
        2: Result := '';
        3: Result := '';
        4: Result := '';
    else Result := '';
    end;
end;

function TRiik.GetFieldValue(i: Integer): Variant;
begin
    Result := null;
    case i of
        0: Result := id;
        1: Result := kood;
        2: Result := nimi;
        3: Result := seletus;
        4: Result := eukood;
        else Result := null;
    end;
end;

function TRiik.GetFieldSize(i: Integer): Integer;
begin
    case i of
        0: Result := 0;
        1: Result := 20;
        2: Result := 100;
        3: Result := 1000;
        4: Result := 2;
        else Result := 0;
    end;
end;

function TRiik.FieldCount: Integer;
begin
    Result := 5;
end;

function TRiik.IsUnique: Boolean;
begin
    try
        qry.Close;
        qry.SQL.Text := 'SELECT COUNT(*) FROM RIIGID WHERE ' +
                'KOOD = ' + Quote(kood) +
            ' AND ID <> ' + IntToStr(id);
        qry.ExecQuery;
        Result := qry.Fields[0].AsInteger = 0;
        qry.Close;
    except
        on e: Exception do
        begin
            LogError(e);
            Result := false;
        end;
    end;
end;

function TRiik.GetDeleteSQL: String;
begin
    Result := 'DELETE FROM RIIGID WHERE ID = ' + IntToStr(id);
end;

function TRiik.DeleteCascades(bSoft: Boolean = true): Boolean;
begin
    Result := false;
    try
        qry.Close;
        //parandame pehmeid seoseid:
        if bSoft then
        begin
        end;
        Result := true;
    except
        on e: Exception do
            LogError(e);
    end;
end;

procedure TRiik.GetRplCascades(sl: TStringList);
begin
    sl.Clear();
end;

procedure TRiik.ClearReplicationSchedule;
begin
    try
        qry.Close;
        qry.SQL.Text := 'DELETE FROM REPLICATION WHERE TABLENAME = ''RIIGID'' AND HASHCODE = ''' + IntToStr(id) + '''';
        qry.ExecQuery;
    except
    end;
end;

function TRiik.InnerCanDelete: Boolean;
begin
    Result := false;
    try
        if GetCount('SELECT COUNT(*) FROM KAUBAD WHERE RIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM MYYGITELLIMUSED WHERE OBJAADRRIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM FIRMAD WHERE JURAADRESSRIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM FIRMAD WHERE POSTIAADRESSRIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM SAATELEHED WHERE RIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM TOOTAJAD WHERE RIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        if GetCount('SELECT COUNT(*) FROM KAUBALIIKUMISED WHERE OBJAADRRIIKID = ' + IntToStr(id), 1) > 0 then
            Exit;
        Result := true;
    except
        on e: Exception do
            LogError(e);
    end;
end;

function TRiik.doLoad: Boolean;
begin
    Result := false;
    try
        if (id < 1) and ((kood = '')) then
        begin
            Clear;
            Result := true;
            Exit;
        end;
        qry.Close;
        if id < 1 then
            qry.SQL.Text := 'SELECT ' +
                'ID' +
                ', KOOD' +
                ', NIMI' +
                ', SELETUS' +
                ', EUKOOD' +
                ' FROM RIIGID WHERE ' +
                'KOOD = ' + Quote(kood) + ' order by id desc'
        else
            qry.SQL.Text := 'SELECT ' +
                'ID' +
                ', KOOD' +
                ', NIMI' +
                ', SELETUS' +
                ', EUKOOD' +
                ' FROM RIIGID WHERE ID = ' + IntToStr(id);
        qry.ExecQuery;
        id := qry.Fields[0].AsInteger;
        kood := qry.Fields[1].AsString;
        nimi := qry.Fields[2].AsString;
        seletus := qry.Fields[3].AsString;
        eukood := qry.Fields[4].AsString;
        qry.Close;
        Result := true;
    except
        on e: Exception do
            LogError(e);
    end;
end;

function TRiik.doSave: Boolean;
begin
    Result := false;
    try
        qry.Close;
        if id < 1 then
        begin
            qry.SQL.Text := 'INSERT INTO RIIGID(' +
                ' KOOD' +
                ', NIMI' +
                ', SELETUS' +
                ', EUKOOD' +
                ')VALUES(' +
                 Quote(kood) +
                ', ' + Quote(nimi) +
                ', ' + Quote(seletus) +
                ', ' + Quote(eukood) +
                ')';
            qry.ExecQuery;
            Load;
        end
        else
        begin
            qry.SQL.Text := 'UPDATE RIIGID SET' +
                ' KOOD = ' + Quote(kood) +
                ', NIMI = ' + Quote(nimi) +
                ', SELETUS = ' + Quote(seletus) +
                ', EUKOOD = ' + Quote(eukood) +
                ' WHERE ID = ' + IntToStr(id);
            qry.ExecQuery;
        end;
        Result := true;
    except
        on e: Exception do
            LogError(e);
    end;
end;

function TRiik.doReplicationPost: Boolean;
begin
    Result := false;
    try
        qry.Close;
        qry.SQL.Text := 'INSERT INTO RIIGID(' +
                ' ID' +
                ', KOOD' +
                ', NIMI' +
                ', SELETUS' +
                ', EUKOOD' +
            ')VALUES(' +
                 IntToStr(id) +
                ', ' + Quote(kood) +
                ', ' + Quote(nimi) +
                ', ' + Quote(seletus) +
                ', ' + Quote(eukood) +
            ')';
        qry.ExecQuery;
        Result := true;
    except
        on e: Exception do
            LogError(e);
    end;
end;

function TRiik.IsReplicationExists: Boolean;
begin
    Result := false;
    try
        qry.Close;
        qry.SQL.Text := 'SELECT COUNT(*) FROM RIIGID WHERE ID = ' + IntToStr(ID);
        qry.ExecQuery;
        Result := (qry.Fields[0].AsInteger > 0);
        qry.Close;
    except
        on e: Exception do
            LogError(e);
    end;
end;

procedure TRiik.Clear;
begin
    id := 0;
    kood := '';
    nimi := '';
    seletus := '';
    eukood := '';
end;

function TRiik.RegID: Integer;
begin
    Result := 9000;
end;

function TRiik.LoadByKNKood(s: String): Boolean;
begin
    Result := false;
    try
        qry.Close;
        qry.SQL.Text := 'SELECT ID FROM RIIGID WHERE EUKOOD = ' + Quote(s);
        qry.ExecQuery;
        if qry.Fields[0].AsInteger > 0 then
        begin
            ID := qry.Fields[0].AsInteger;
            Result := load;
        end;
        qry.Close;
    except
    end;
end;

end.
