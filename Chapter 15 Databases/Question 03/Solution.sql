UPDATE Requests
SET Status = 'Close'
WHERE AptID IN (
    SELECT AptID FROM Apartments
    WHERE BuildingID = 11
) AND Status = 'Open';  