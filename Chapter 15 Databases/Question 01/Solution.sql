SELECT TenantName FROM Tenants
INNER JOIN (
    SELECT TenantID FROM AptTenants
    GROUP BY TenantID
    HAVING COUNT(TenantID) > 1
) TenantIDs ON Tenants.TenantID = TenantIDs.TenantID;